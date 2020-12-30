#include "Text.h"
#include "Undo.h"

extern Undo undo;

Text::Text(const std::string& l, const File& f, Composite* p)
	: Leaf(l, f, p, Leaf::Text)
{
	load_from_file();
}

void Text::set_text(const std::string& t)
{
	undo.text_save(this, text);
	text = t;
}

void Text::write_to_file(File* file) const 
{
	*file << std::to_string(get_type()) << " " << get_label() << " " << get_file()->get_filename() << "\n";

	File* f = get_file();
    f->open(f->get_filename(), File::create);

	*f << text;
}

void Text::load_from_file() 
{
	File* f = get_file();
	*f >> text;
    f->clear();
}
