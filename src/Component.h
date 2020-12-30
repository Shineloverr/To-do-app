#pragma once

#include "File.h"

#include <string>
#include <iostream>
//#include <QtWidgets>

class Composite;

class Component
{
public:
	friend class Undo;

	Component();

	Component(const std::string& l, const File& f, Composite* p = nullptr);

	const std::string get_label() const;

    virtual void set_label(const std::string& l);

	virtual void load_from_file() = 0;

	virtual void write_to_file(File*) const = 0;

	virtual ~Component();

	virtual void remove() = 0;

	virtual void add_component(const std::string&, const std::string&, std::ios::openmode) = 0;

	virtual std::shared_ptr<Component> get_child(std::size_t indx) const = 0;

	virtual void remove_component(std::size_t indx) = 0;

protected:
	File* get_file() const;

    void set_label_without_store(const std::string& l);

private:
	std::string label;
	Composite* parent;
	File* file;
};
