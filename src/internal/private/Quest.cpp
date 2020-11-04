#include "../public/Quest.h"

Quest::Quest()
{
}

Quest::Quest(std::string Name, bool IsMain, int World, int ParentQuest, bool IsFailable, bool IsOptional)
{
	Quest::Name = Name;
	Quest::IsMain = IsMain;
	Quest::World = World;
	Quest::ParentQuest = ParentQuest;
	Quest::IsFailable = IsFailable;
	Quest::IsOptional = IsOptional;
}

unsigned int Quest::GetColumnCount() const
{
	return 0;
}

wxString Quest::GetColumnType(unsigned int col) const
{
	return wxString();
}

void Quest::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
{
}

bool Quest::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
{
	return false;
}

wxDataViewItem Quest::GetParent(const wxDataViewItem& item) const
{
	return wxDataViewItem();
}

bool Quest::IsContainer(const wxDataViewItem& item) const
{
	return false;
}

unsigned int Quest::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
{
	return 0;
}
