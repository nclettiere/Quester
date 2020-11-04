#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/dataview.h>

#include <iostream>

class Quest : wxDataViewModel
{
private:
	std::string Name;
	bool IsMain;
	int World;
	int ParentQuest;
	bool IsFailable;
	bool IsOptional;

public:
	Quest();
	Quest(
		std::string Name,
		bool IsMain,
		int World,
		int ParentQuest,
		bool IsFailable,
		bool IsOptional);

	// Inherited via wxDataViewModel
	virtual unsigned int GetColumnCount() const override;
	virtual wxString GetColumnType(unsigned int col) const override;
	virtual void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;
	virtual bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;
	virtual wxDataViewItem GetParent(const wxDataViewItem& item) const override;
	virtual bool IsContainer(const wxDataViewItem& item) const override;
	virtual unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;
};

