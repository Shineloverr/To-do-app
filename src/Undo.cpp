#include "Undo.h"

extern Undo undo;

Undo::Undo()
	: parent(nullptr),
	indx(0),
	obj(nullptr),
	was_restored(true),
	cundo(new Leaf_undo())
{ }

void Undo::save(Composite* p, std::size_t i, std::shared_ptr<Component> del, Mode m, const std::string& label /* = "" */,
				std::vector<std::shared_ptr<Component>>* cnt /* = nullptr */)
{
	if (obj && mode == Removed)
	{
		obj->remove();    
	}
    obj = nullptr;

	parent = p;
	indx = i;
	obj = del;
	mode = m;
	was_restored = false;
	this->label = label;
	
	if (p == nullptr && cnt)
	{
		contents = cnt;
		type = Brd;
	}
	else
	{
		type = Compos;
	}
}

void Undo::compos_restore()
{
	if (parent)
	{
		switch (mode)
		{
		case Removed:
			parent->contents.emplace(parent->contents.begin() + indx, obj);
			break;
		case Changed:
			parent->contents[indx]->label = label;
			break;
		case Added:
			parent->contents.erase(parent->contents.begin() + indx);
			obj->remove();
			break;
		default:
			break;
		}
	}
}

void Undo::restore()
{
	if (!was_restored)
	{
		switch (type)
		{
		case Check:
			cundo->checklist_restore();
			break;
		case Txt:
			cundo->text_restore();
            break;
		case Compos:
			compos_restore();
			break;
		case Brd:
			board_restore();
			break;
        case Rem:
            cundo->reminder_restore();
            break;
		default:
			break;
		}
	}

    was_restored = true;
    obj = nullptr;
}

void Undo::board_restore()
{
	switch (mode)
	{
	case Removed:
		contents->emplace(contents->begin() + indx, obj);
		break;
	case Changed:
		(*contents)[indx]->label = label;
		break;
	case Added:
		contents->erase(contents->begin() + indx);
		obj->remove();
		break;
	default:
		break;
	}
}

void restore()
{
	undo.restore();
}

Undo::~Undo()
{
	if (!was_restored && mode == Removed)
	{
		obj->remove();
	}
    else
    {
        obj = nullptr;
    }

    was_restored = true; // to somehow destructor won't call obj->remove() twice
}

void Undo::checklist_save(Checklist* p, std::pair<std::string, bool>& ob, std::size_t i, Mode m)
{
	was_restored = false;
	type = Check;
	cundo->checklist_save(p, ob, i, m);
}

void Undo::text_save(Text* p, const std::string& ob)
{
	was_restored = false;
	type = Txt;
	cundo->text_save(p, ob);
}

void Undo::reminder_save(Reminder *p, const QDateTime& dt)
{
    was_restored = false;
    type = Rem;
    cundo->reminder_save(p, dt);
}

Leaf_undo::Leaf_undo() { }

void Leaf_undo::text_save(Text* p, const std::string& ob)
{
	text_parent = p;
	obj.first = ob;
}

void Leaf_undo::checklist_save(Checklist* p, std::pair<std::string, bool>& ob, std::size_t i, Undo::Mode m)
{
	ch_parent = p;
	obj = ob;
	indx = i;
	mode = m;
}

void Leaf_undo::reminder_save(Reminder *p, const QDateTime& dt)
{
    reminder_parent = p;
    qdt = dt;
}

void Leaf_undo::text_restore()
{
	text_parent->text = obj.first;
	text_parent = nullptr;
}

void Leaf_undo::reminder_restore()
{
    reminder_parent->dtime = qdt;
    reminder_parent = nullptr;
}

void Leaf_undo::checklist_restore()
{
	switch (mode)
	{
	case Undo::Removed:
		ch_parent->tasks.emplace(ch_parent->tasks.begin() + indx, obj);
		break;
	case Undo::Changed:
		ch_parent->tasks[indx] = obj;
		break;
	case Undo::Added:
		ch_parent->tasks.erase(ch_parent->tasks.begin() + indx);
		break;
	default:
		break;
	}

	ch_parent = nullptr;
}
