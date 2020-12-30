#pragma once

#include "Leaf.h"

#include <vector>

class Checklist : public Leaf
{
public:
	friend class Leaf_undo;

	Checklist(const std::string& label, const File& file, Composite* parent = nullptr);

	virtual void write_to_file(File* f) const override;

	virtual void load_from_file() override;

	void add(const std::string& task);

    void remove_task(std::size_t indx);

	void change_task(std::size_t indx, const std::string& task);

	void set_result(std::size_t indx, bool is_compl = true);

    inline bool is_checked(std::size_t indx) const { return tasks[indx].second; }

    inline const std::string get_task(std::size_t indx) const { return tasks[indx].first; }

    inline std::size_t size() const { return tasks.size(); }
	
private:
	std::vector<std::pair<std::string, bool>> tasks;
};
