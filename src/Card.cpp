#include "Card.h"
#include "SystemTray.h"

Card::Card(const std::string& l, const File& f, Composite* p /* = nullptr */)
	: Composite(l, f, p)
{
	load_from_file();
}

void Card::add_component(const std::string& label, const std::string& filename, std::ios::openmode mode) 
{

}

void Card::load_from_file() 
{
	if (!get_file()->empty())
	{
		File* f = get_file();
		std::string type;
		std::string label;
		std::string filename;

		while (*f >> type >> label >> filename)
		{
			Leaf::Type ch_type = static_cast<Leaf::Type>(std::stoi(type));
            create_child(label, filename, ch_type, File::open_exst);
		}
	}
}

Leaf* Card::create_child(const std::string& label, const std::string& filename, Leaf::Type ch_type, std::ios::openmode mode)
{
	std::shared_ptr<Leaf> child;

	switch (ch_type)
	{
	case Leaf::Reminder:
        child = std::make_shared<Reminder>(label, File(filename, mode), this);
		break;
	case Leaf::Text:
        child = std::make_shared<Text>(label, File(filename, mode), this);
		break;
	case Leaf::Checklist:
        child = std::make_shared<Checklist>(label, File(filename, mode), this);
		break;
	default:
		break;
	}

	add(child);

    return child.get();
}
