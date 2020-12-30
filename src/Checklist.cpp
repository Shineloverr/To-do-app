#include "Checklist.h"
#include "Undo.h"

extern Undo undo;

Checklist::Checklist(const std::string& label, const File& file, Composite* parent /* = nullptr */)
	: Leaf(label, file, parent, Leaf::Checklist)
{
	load_from_file();
}

void Checklist::write_to_file(File* f) const
{
	*f << std::to_string(get_type()) << " " << get_label() << " " << get_file()->get_filename() << "\n";

	File* file = get_file();
    file->open(file->get_filename(), File::create);

	for (auto i : tasks)
	{
		*file << i.first << " " << std::to_string(i.second) << "\n";
	}
}

void Checklist::load_from_file()
{
	File* f = get_file();

	std::string task;
	std::string is_completed;

	while (*f >> task >> is_completed)
	{
		tasks.emplace_back(std::pair<std::string, bool>(task, std::stoi(is_completed)));
	}

    f->clear();
}

void Checklist::add(const std::string& task)
{
	tasks.emplace_back(std::pair<std::string, bool>(task, false));
	undo.checklist_save(this, tasks.back(), tasks.size() - 1, Undo::Added);
}

void Checklist::remove_task(std::size_t indx)
{
	undo.checklist_save(this, tasks[indx], indx, Undo::Removed);
	tasks.erase(tasks.begin() + indx);
}

void Checklist::change_task(std::size_t indx, const std::string& task)
{
	undo.checklist_save(this, tasks[indx], indx, Undo::Changed);
	tasks[indx].first = task;
}

void Checklist::set_result(std::size_t indx, bool is_compl /* = true */)
{
	undo.checklist_save(this, tasks[indx], indx, Undo::Changed);
	tasks[indx].second = is_compl;
}
