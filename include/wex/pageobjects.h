/*
BSD 3-Clause License

Copyright (c) Alliance for Sustainable Energy, LLC. See also https://github.com/NREL/wex/blob/develop/LICENSE
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __pageobjects_h
#define __pageobjects_h

#include <wx/clrpicker.h>
#include <wx/spinctrl.h>

#include "wex/pagelayout.h"

class wxPageTextObject;

class wxPageTextObjectEditDialog : public wxDialog {
public:
    wxPageTextObjectEditDialog(wxWindow *parent);

    void SetData(wxPageTextObject *obj, wxPageLayoutCtrl *layout);

    void GetData(wxPageTextObject *obj);

    void OnSpin(wxSpinEvent &e) { OnChange(e); }

    void OnColour(wxColourPickerEvent &e) { OnChange(e); }

    void OnChange(wxCommandEvent &);

    void OnSymbol(wxCommandEvent &);

protected:
DECLARE_EVENT_TABLE()
    wxBoxSizer *m_toolSizer;
    wxTextCtrl *m_txtData;
    wxCheckBox *m_chkBold, *m_chkItalic;
    wxComboBox *m_cboFace;
    wxComboBox *m_cboAlign;
    wxSpinCtrl *m_spnSize;
    wxColourPickerCtrl *m_cpcColour;
    wxPageLayoutCtrl *m_layoutCtrl;
    wxPageTextObject *m_textObject;
};

class wxPageTextObject : public wxPageObject {
public:
    wxPageTextObject();

    virtual ~wxPageTextObject() {}

    virtual wxString TypeName() { return "wxPageTextObject"; }

    virtual wxString Description() { return "Text Object"; }

    virtual wxPageObject *Duplicate();

    virtual bool Copy(wxPageObject *obj);

    virtual bool EditObject(wxPageLayoutCtrl *);

    virtual void Render(wxPageOutputDevice &);

    virtual bool ReadData(wxInputStream &is);

    virtual bool WriteData(wxOutputStream &os);

    void SetText(const wxString &text);

    wxString GetText() { return m_text; }

    void SetSize(int points);

    int GetSize() { return m_size; }

    void SetColour(const wxColour &c) { m_colour = c; }

    wxColour GetColour() { return m_colour; }

    void SetFace(int face) { m_face = face; } // wxPageOutputDevice::FontFace
    int GetFace() { return m_face; }

    void SetBold(bool b) { m_bold = b; }

    bool GetBold() { return m_bold; }

    void SetItalic(bool b) { m_italic = b; }

    bool GetItalic() { return m_italic; }

    void SetAlign(int align) { m_align = align; } // wxLEFT, wxCENTER, wxRIGHT
    int GetAlign() { return m_align; }

protected:
    wxString m_text;
    int m_face, m_size, m_align;
    wxColour m_colour;
    bool m_bold, m_italic;
};

class wxPageImageObject : public wxPageObject {
public:
    wxPageImageObject() {}

    virtual ~wxPageImageObject() {}

    virtual wxString TypeName() { return "wxPageImageObject"; }

    virtual wxString Description() { return "Image Object"; }

    virtual wxPageObject *Duplicate();

    virtual bool Copy(wxPageObject *obj);

    virtual bool EditObject(wxPageLayoutCtrl *);

    virtual void Render(wxPageOutputDevice &);

    virtual bool ReadData(wxInputStream &is);

    virtual bool WriteData(wxOutputStream &os);

protected:
    wxImage m_image;
};

#endif
