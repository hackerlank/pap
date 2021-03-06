#ifndef __SkillObjectTree_H__
#define __SkillObjectTree_H__

#include <wx/treectrl.h>
#include "OgreParticle.h"
#include "EffectSystem/FairySkill.h"
class SkillObjectEditor;

class SkillTreeItemData : public wxTreeItemData
{
public:
	SkillTreeItemData(const wxString& desc,const wxString& value = "",void* data = NULL) : m_desc(desc),m_value(value),m_data(data){ }

	void ShowInfo(wxTreeCtrl *tree);
	const wxString& GetDesc() const { return m_desc; }
	const void* GetData() const {return m_data;}
	const wxString& GetValue() const {return m_value;}

private:
	wxString m_desc;
	wxString m_value;
	void* m_data;
};

class SkillObjectTree : public wxTreeCtrl
{
public:

	enum
	{
		TreeCtrlIcon_Skill,
		TreeCtrlIcon_AnimEffect,
		TreeCtrlIcon_CameraShake,
		TreeCtrlIcon_Ribbon,
		TreeCtrlIcon_Sound,
		TreeCtrlIcon_SceneLight,
		TreeCtrlIcon_BulletFlow,
		TreeCtrlIcon_SkilltProperty,
	};
  
    SkillObjectTree() { }
	SkillObjectTree(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style =  wxTAB_TRAVERSAL)
        : wxTreeCtrl(parent, id, pos, size, style)
    {
		m_reverseSort = false;
		mSelectSkillObject = NULL;

		CreateImageList();

    }
    virtual ~SkillObjectTree()
    {

    }
	void AddSkillToTree(Fairy::Skill *pSkill);
    virtual long MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam);

	void SelectSkillSetting();
	void SelectElementItem(Ogre::StringInterface* element);
	void CreateImageList(int size = 16);

	void OnBeginDrag(wxTreeEvent& event);
	void OnBeginRDrag(wxTreeEvent& event);
	void OnEndDrag(wxTreeEvent& event);
	void OnBeginLabelEdit(wxTreeEvent& event);
	void OnEndLabelEdit(wxTreeEvent& event);
	void OnDeleteItem(wxTreeEvent& event);
	void OnContextMenu(wxContextMenuEvent& event);
	void OnItemMenu(wxTreeEvent& event);
	void OnGetInfo(wxTreeEvent& event);
	void OnSetInfo(wxTreeEvent& event);
	void OnItemExpanded(wxTreeEvent& event);
	void OnItemExpanding(wxTreeEvent& event);
	void OnItemCollapsed(wxTreeEvent& event);
	void OnItemCollapsing(wxTreeEvent& event);
	void OnSelChanged(wxTreeEvent& event);
	void OnSelChanging(wxTreeEvent& event);
	void OnTreeKeyDown(wxTreeEvent& event);
	void OnItemActivated(wxTreeEvent& event);
	void OnItemRClick(wxTreeEvent& event);

	void OnRMouseDown(wxMouseEvent& event);
	void OnRMouseUp(wxMouseEvent& event);
	void OnRMouseDClick(wxMouseEvent& event);

	void OnMenu(wxCommandEvent & event);

	void GetItemsRecursively(const wxTreeItemId& idParent,
		wxTreeItemIdValue cookie = 0);


	void DoSortChildren(const wxTreeItemId& item, bool reverse = false)
	{ m_reverseSort = reverse; wxTreeCtrl::SortChildren(item); }
	void DoEnsureVisible() { if (m_lastItem.IsOk()) EnsureVisible(m_lastItem); }

	void ShowMenu(wxTreeItemId id, const wxPoint& pt);

	int ImageSize(void) const { return m_imageSize; }

	void SetLastItem(wxTreeItemId id) { m_lastItem = id; }
	//刷新选择item
	void refrashSelected();

	//更新制定类型名称的属性
	void refreshItem(const wxString& Desc,const wxString& propertyName,void* data = NULL);

	Ogre::StringInterface* GetSelectSkillObject(){return mSelectSkillObject;}
	void SetSelectSkillObject(Ogre::StringInterface* object){mSelectSkillObject = object;}

protected:


	virtual int OnCompareItems(const wxTreeItemId& i1, const wxTreeItemId& i2);

	// is this the test item which we use in several event handlers?
	bool IsTestItem(const wxTreeItemId& item)
	{
		// the test item is the first child folder
		return GetItemParent(item) == GetRootItem() && !GetPrevSibling(item);
	}
	Ogre::StringInterface* mSelectSkillObject;
private:

	void LogEvent(const wxChar *name, const wxTreeEvent& event);

	int          m_imageSize;               // current size of images
	bool         m_reverseSort;             // flag for OnCompareItems
	wxTreeItemId m_lastItem,                // for OnEnsureVisible()
		m_draggedItem;             // item being dragged right now

	// NB: due to an ugly wxMSW hack you _must_ use DECLARE_DYNAMIC_CLASS()
	//     if you want your overloaded OnCompareItems() to be called.
	//     OTOH, if you don't want it you may omit the next line - this will
	//     make default (alphabetical) sorting much faster under wxMSW.
	DECLARE_DYNAMIC_CLASS(SkillObjectTree)

    DECLARE_EVENT_TABLE()
};

#endif // __EffectObjectTree_H__
