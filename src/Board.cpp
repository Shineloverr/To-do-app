#include "Board.h"
#include "Undo.h"

extern File MainFile;
extern Undo undo;

Board::Board(const std::string& l, const File& f, Composite* p /*= nullptr*/)
	: Composite(l, f, p)
{
	load_from_file();
}

void Board::add_component(const std::string& label, const std::string& filename, std::ios::openmode mode)
{
	std::shared_ptr<List> list = std::make_shared<List>(label, File(filename, mode), this);
	add(list);
}

void Board::set_label(const std::string& l)
{
    set_label_without_store(l);
}

Board::~Board()
{
	if (get_file()->exists()) // file was deleted, if board was delteted
	{
        std::cout << "Board " << get_label() << "writing to MainFile\n";
        write_to_file(&MainFile);
	}
}

void load_contents(std::vector<std::shared_ptr<Component>>& contents)
{
    std::string label;
    std::string filename;

    while (MainFile >> label >> filename)
    {
        std::shared_ptr<Component> board = std::make_shared<Board>(label, File(filename, File::open_exst));
        contents.emplace_back(board);
    }

    undo.set_restored(true);
    MainFile.clear();
}

void remove_board(std::vector<std::shared_ptr<Component>>& contents, std::size_t indx)
{
    undo.save(nullptr, indx, contents[indx], Undo::Removed, "",  &contents);
    contents.erase(contents.begin() + indx);
}

void set_label(std::vector<std::shared_ptr<Component>>& contents, std::size_t indx, const std::string& label)
{
    undo.save(nullptr, indx, contents[indx], Undo::Changed, contents[indx]->get_label(), &contents);
    contents[indx]->set_label(label);
}

void add_board(std::vector<std::shared_ptr<Component>>& contents, const std::string& label)
{
	contents.emplace_back(std::make_shared<Board>(label, File("data/" + label + ".txt", File::create)));
	undo.save(nullptr, contents.size() - 1, contents.back(), Undo::Added, "", &contents);
}























