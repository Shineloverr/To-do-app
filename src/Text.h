#pragma once

#include "Leaf.h"

#include <vector>

class Text : public Leaf
{
public:
	friend class Leaf_undo;

	Text(const std::string& l, const File& f, Composite* p);

	void set_text(const std::string& t);

	void write_to_file(File* file) const override;

	void load_from_file() override;

    std::string get_text() const { return text; }

    bool empty() const { return !text.size(); }

private:
	std::string text;
};

