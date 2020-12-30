#pragma once

#include "Composite.h"
#include "Checklist.h"
#include "Text.h"
#include "Reminder.h"

void restore();

class Undo
{
public:
	static enum Mode
	{
		Changed = 0,
		Removed,
		Added
	}modes;

	static enum Type
	{
		Compos = 0,
		Brd,
		Check, 
        Txt,
        Rem
	}types;

	Undo();

	void save(Composite* p, std::size_t i, std::shared_ptr<Component> del, Mode m, const std::string& label = "", 
			  std::vector<std::shared_ptr<Component>>* cnt = nullptr);

	void checklist_save(Checklist* p, std::pair<std::string, bool>& ob, std::size_t i, Mode m);

    void reminder_save(Reminder* p, const QDateTime& dt);

	void text_save(Text* p, const std::string& ob);

    void restore();

    inline bool restored() { return was_restored; }

    inline void set_restored(bool value) { was_restored = value; }

	~Undo();

private:
	void compos_restore();

	void board_restore();

    Leaf_undo* cundo;
	Composite* parent;
    std::size_t indx;
	std::shared_ptr<Component> obj;
	std::string label; // Using for Changed mode only
	bool was_restored;
	Mode mode;
	Type type;
	std::vector<std::shared_ptr<Component>>* contents; // for Brd mode only
};

class Leaf_undo
{
public:
	Leaf_undo();

	void text_save(Text* p, const std::string& ob);

	void checklist_save(Checklist* p, std::pair<std::string, bool>& ob, std::size_t i, Undo::Mode m);

    void reminder_save(Reminder* p, const QDateTime& dt);

	void text_restore();

	void checklist_restore();

    void reminder_restore();

private:
	Checklist* ch_parent;
	Text* text_parent;
    Reminder* reminder_parent;
    QDateTime qdt;
	std::pair<std::string, bool> obj;
	std::size_t indx;
	Undo::Mode mode;
};






