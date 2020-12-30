#pragma once

#include "Composite.h"
#include "Card.h"

class List : public Composite
{
public:
	List(const std::string& l, const File& f, Composite* p = nullptr);

	virtual void add_component(const std::string& l, const std::string& f, std::ios::openmode m) override;
};
