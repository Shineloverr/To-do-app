#pragma once

#include "Composite.h"
#include "List.h"

class Board : public Composite
{
public:
	Board(const std::string& l, const File& f, Composite* p = nullptr);

	void add_component(const std::string& label, const std::string& filename, std::ios::openmode mode) override;

    virtual void set_label(const std::string& l) override;

	virtual ~Board() override;
};

void load_contents(std::vector<std::shared_ptr<Component>>& contents);

void add_board(std::vector<std::shared_ptr<Component>>& contents, const std::string& label);

void remove_board(std::vector<std::shared_ptr<Component>>& contents, std::size_t indx);

void set_label(std::vector<std::shared_ptr<Component>>& contents, std::size_t indx, const std::string& label);

