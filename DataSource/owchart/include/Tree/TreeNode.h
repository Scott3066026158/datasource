/*********************************************************************************\
*                                                                                 *
* TreeNode.h - Tree node functions, types, and definitions                        *
*                                                                                 *
*               Version 4.00 ¡ï¡ï¡ï¡ï¡ï                                           *
*                                                                                 *
*               Copyright (c) 2016-2016, Lord's tree. All rights reserved.        *
*               Check 2016/9/23 by Lord.                                          *
*                                                                                 *
***********************************************************************************/

#ifndef __TREENODE_H__
#define __TREENODE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Grid\\Grid.h"
#include "..\\Grid\\GridRow.h"
#include "..\\Grid\\GridCell.h"
#include "..\\Button\\CheckBox.h"
#include "Tree.h"

namespace OwLib
{
	class  TreeA;

	class  TreeNodeA : public GridControlCell
	{
	protected:
		bool m_allowDragIn;
		bool m_allowDragOut;
		bool m_checked;
		vector<TreeNodeA*> m_nodes;
		bool m_expended;
		int m_indent;
		TreeNodeA *m_parent;
		GridColumn *m_targetColumn;
		wstring m_text;
		TreeA *m_tree;
		wstring m_value;
		void CheckChildNodes(vector<TreeNodeA*> nodes, bool isChecked);
		void CollapseChildNodes(vector<TreeNodeA*> nodes, bool collapseAll);
		void ExpendChildNodes(vector<TreeNodeA*> nodes, bool parentExpened, bool expendAll);
		TreeNodeA* GetLastNode(vector<TreeNodeA*> nodes);
	public:
		TreeNodeA();
		virtual ~TreeNodeA();
		virtual bool AllowDragIn();
		virtual void SetAllowDragIn(bool allowDragIn);
		virtual bool AllowDragOut();
		virtual void SetAllowDragOut(bool allowDragOut);
		virtual bool IsChecked();
		virtual void SetChecked(bool checked);
		virtual bool IsExpended();
		virtual void SetExpended(bool expended);
		virtual int GetIndent();
		virtual TreeNodeA* GetParent();
		virtual void SetParent(TreeNodeA *parent);
		virtual GridColumn* GetTargetColumn();
		virtual void SetTargetColumn(GridColumn *targetColumn);
		virtual TreeA* GetTree();
		virtual void SetTree(TreeA *tree);
		virtual wstring GetValue();
		virtual void SetValue(const wstring& value);
	public:
		void AppendNode(TreeNodeA *node);
		void ClearNodes();
		void Collapse();
		void CollapseAll();
		void Expend();
		void ExpendAll();
		vector<TreeNodeA*> GetChildNodes();
		int GetNodeIndex(TreeNodeA *node);
		virtual wstring GetPaintText();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual wstring GetString();
		void InsertNode(int index, TreeNodeA *node);
		bool IsNodeVisible(TreeNodeA *node);
		virtual void OnAddingNode(int index);
		virtual void OnPaintCheckBox(CPaint *paint, const RECT& rect);
		virtual void OnPaintNode(CPaint *paint, const RECT& rect);
		virtual void OnPaint(CPaint *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnRemovingNode();
		void RemoveNode(TreeNodeA *node);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void SetString(const wstring& value);
	};
}

#endif