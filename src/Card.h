#pragma once

#include "Composite.h"
#include "Leaf.h"
#include "Text.h"
#include "Checklist.h"
#include "Reminder.h"

class Card : public Composite
{
public:
	Card(const std::string& l, const File& f, Composite* p = nullptr);

	void add_component(const std::string& label, const std::string& filename, std::ios::openmode mode) override;

	void load_from_file() override;

    Leaf* create_child(const std::string& label, const std::string& filename, Leaf::Type ch_type, std::ios::openmode mode);
};
