#include "Undo.h"

extern Undo undo;

Component::Component()
{ }

Component::Component(const std::string& l, const File& f, Composite* p /* = nullptrc*/)
	: label(l), parent(p), file(new File(f))
{ }

void Component::set_label(const std::string& l)
{
	int indx = parent->get_indx(this); // number of this object in parent's content vector
	undo.save(parent, indx, parent->get_child(indx), Undo::Changed, label);
	label = l;
}

void Component::set_label_without_store(const std::string& l) { label = l; }

const std::string Component::get_label() const { return label; }

File* Component::get_file() const { return file; }

Component::~Component() { file->close(); }
