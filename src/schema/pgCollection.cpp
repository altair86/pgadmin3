//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// Copyright (C) 2002, The pgAdmin Development Team
// This software is released under the pgAdmin Public Licence
//
// pgCollection.cpp - Simple object for use with 'collection' nodes
//
//////////////////////////////////////////////////////////////////////////

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "pgAdmin3.h"
#include "pgCollection.h"
#include "pgServer.h"
#include "pgGroup.h"
#include "pgUser.h"
#include "pgLanguage.h"
#include "pgAggregate.h"
#include "pgCast.h"
#include "pgConversion.h"
#include "pgDomain.h"
#include "pgFunction.h"
#include "pgOperator.h"
#include "pgOperatorClass.h"
#include "pgSequence.h"
#include "pgTable.h"
#include "pgType.h"
#include "pgView.h"
#include "pgCheck.h"
#include "pgColumn.h"
#include "pgForeignKey.h"
#include "pgIndex.h"
#include "pgRule.h"
#include "pgTrigger.h"

#include "frmMain.h"

extern char *typeNameList[]; 

pgCollection::pgCollection(int newType)
: pgObject(newType, typeNameList[newType])
{ 
    wxLogInfo(wxT("Creating a pgCollection object")); 
}

pgCollection::~pgCollection()
{
    wxLogInfo(wxT("Destroying a pgCollection object"));
}


void pgCollection::ShowList(const wxString& name, wxTreeCtrl *browser, wxListCtrl *properties)
{
    if (properties)
    {
        // Display the properties.
        long cookie;
        pgObject *data;

        // Setup listview
        CreateListColumns(properties, name, wxT("Comment"));

        wxTreeItemId item = browser->GetFirstChild(GetId(), cookie);
        long pos=0;
        while (item)
        {
            data = (pgObject *)browser->GetItemData(item);
            if (data->GetType() == GetType()+1)
            {
                properties->InsertItem(pos, data->GetFullName(), 0);
                properties->SetItem(pos, 1, data->GetComment());
            }
            // Get the next item
            item = browser->GetNextChild(GetId(), cookie);
            pos++;
        }
    }
}



void pgCollection::UpdateChildCount(wxTreeCtrl *browser, int substract)
{
    wxString label;
    label.Printf(GetName() + wxT(" (%d)"), browser->GetChildrenCount(GetId(), FALSE) -substract);
    browser->SetItemText(GetId(), label);
}



void pgCollection::SetSql(wxTreeCtrl *browser, ctlSQLBox *sqlPane, int index)
{
    sqlPane->Clear();

    long cookie;
    pgObject *data;

    wxTreeItemId item = browser->GetFirstChild(GetId(), cookie);
    long pos=0;
    while (item)
    {
        data = (pgObject *)browser->GetItemData(item);
        if (data->GetType() == GetType()+1)
        {
            if (index == pos)
            {
                sqlPane->SetText(data->GetSql(browser));
                return;
            }
            pos++;
        }
        item = browser->GetNextChild(GetId(), cookie);
    }
}



void pgCollection::ShowTreeDetail(wxTreeCtrl *browser, frmMain *form, wxListCtrl *properties, wxListCtrl *statistics, ctlSQLBox *sqlPane)
{
    switch (GetType())
    {
        case PG_DATABASES:
            pgDatabase::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_GROUPS:
            pgGroup::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_USERS:
            pgUser::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_LANGUAGES:
            pgLanguage::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_SCHEMAS:
            pgSchema::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_AGGREGATES:
            pgAggregate::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_CASTS:
            pgCast::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_CONVERSIONS:
            pgConversion::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_DOMAINS:
            pgDomain::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_FUNCTIONS:
        case PG_TRIGGERFUNCTIONS:
            pgFunction::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_OPERATORS:
            pgOperator::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_OPERATORCLASSES:
            pgOperatorClass::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_SEQUENCES:
            pgSequence::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_TABLES:
            pgTable::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_TYPES:
            pgType::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_VIEWS:
            pgView::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_CHECKS:
            pgCheck::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_COLUMNS:
            pgColumn::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_FOREIGNKEYS:
            pgForeignKey::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_INDEXES:
            pgIndex::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_RULES:
            pgRule::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        case PG_TRIGGERS:
            pgTrigger::ShowTreeCollection(this, form, browser, properties, statistics, sqlPane);
            break;
        default:
            return;
    }
    UpdateChildCount(browser);
    if (properties)
        ShowList(typeNameList[GetType()+1], browser, properties);
}
