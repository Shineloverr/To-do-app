#include "Composite.h"
#include "Undo.h"

extern Undo undo;

Composite::Composite(const std::string& l, const File& f, Composite* p)
	: Component(l, f, p)
{ }

void Composite::remove_component(std::size_t indx)
{
	if (indx < contents.size())
	{
		undo.save(this, indx, contents[indx], Undo::Removed);
		contents.erase(contents.begin() + indx);
	}
}

std::shared_ptr<Component> Composite::get_child(std::size_t indx) const
{
	return indx >= contents.size() ? nullptr : contents[indx];
}

void Composite::add(std::shared_ptr<Component> c)
{
	contents.emplace_back(c);
	undo.save(this, contents.size() - 1, contents.back(), Undo::Added);
}

void Composite::load_from_file()
{
	if (!get_file()->empty())
	{
		std::string child_name;
		std::string file_name;
		File* f = get_file();

		while (*f >> child_name >> file_name)
		{
			add_component(child_name, file_name, File::open_exst);
		}
	}
}

void Composite::write_to_file(File* f) const
{
	*f << get_label() << " " << get_file()->get_filename() << "\n";

	File* file = get_file();
	file->close();
	file->open(file->get_filename(), File::create); // remove contets to write new

	for (auto i : contents)
	{
		i->write_to_file(file);
	}
}

void Composite::remove()
{
	for (auto i : contents)
	{
		i->remove();
	}

	get_file()->delete_file();
}

void Composite::add(std::shared_ptr<Component> c, std::size_t indx)
{
	contents.emplace(contents.begin() + indx, c);
	undo.save(this, indx, contents[indx], Undo::Added);
}

std::size_t Composite::get_indx(Component* obj) const
{
    for (std::size_t i = 0; i < contents.size(); i++)
	{
		if (obj == contents[i].get())
		{
			return i;
		}
	}

    return contents.size();
}
