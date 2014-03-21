#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/stc/stc.h>
#include <wx/webview.h>
#include <wx/statbmp.h>
#include <wx/numformatter.h>
#include <wx/grid.h>

#include "wex/icons/time.cpng"
#include "wex/icons/dmap.cpng"
#include "wex/icons/calendar.cpng"
#include "wex/icons/barchart.cpng"
#include "wex/icons/curve.cpng"
#include "wex/icons/scatter.cpng"


class PngTestApp : public wxApp
{
public:
	bool OnInit()
	{
		wxInitAllImageHandlers();
		wxFrame *frm = new wxFrame(NULL, wxID_ANY, "SchedCtrl", wxDefaultPosition, wxSize(300,200));
		frm->SetBackgroundColour( *wxWHITE );
		wxStaticBitmap *bitmap = new wxStaticBitmap( frm,  wxID_ANY, wxBITMAP_PNG_FROM_DATA( time ) );

		frm->Show();
		return true;
	}
};

//IMPLEMENT_APP( PngTestApp );


#include "wex/plot/plplotctrl.h"
#include "wex/plot/pllineplot.h"
#include "wex/plot/plscatterplot.h"

#include "wex/dview/dvplotctrl.h"
#include "wex/dview/dvselectionlist.h"

#include "wex/codeedit.h"
#include "wex/lkscript.h"
#include "wex/diurnal.h"
#include "wex/utils.h"

#include "wex/metro.h"

#include "wex/icons/cirplus.cpng"
#include "wex/icons/qmark.cpng"

#include "demo_bitmap.cpng"

#include "wex/uiform.h"
#include "wex/snaplay.h"

void TestDVSelectionCtrl()
{
	wxFrame *frame = new wxFrame( 0, wxID_ANY, wxT("wxDVSelectionCtrl in \x01dc\x03AE\x03AA\x00C7\x00D6\x018C\x01dd"), wxDefaultPosition, wxSize(250,510) );
	wxDVSelectionListCtrl *sel = new wxDVSelectionListCtrl( frame, wxID_ANY, 
		2, wxDefaultPosition, wxDefaultSize, wxDVSEL_RADIO_FIRST_COL );
	sel->SetBackgroundColour( *wxWHITE );
	//sel->SetFont( *wxSWISS_FONT );

	for( int gg=1;gg<=3;gg++)
		for( size_t i=0;i<5;i++ )
			sel->Append( wxString::Format("Item %d", (int)i+1) , wxString::Format("Group %d", gg ) );

	sel->Append("Ungrouped A" );
	sel->Append("Ungrouped B" );
	sel->Append("Ungrouped C" );

	frame->Show();

}

void TestSnapLayout( wxWindow *parent )
{
	wxFrame *frame = new wxFrame( parent, wxID_ANY, wxT("wxSnapLayout in \x01dc\x03AE\x03AA\x00C7\x00D6\x018C\x01dd"), wxDefaultPosition, wxSize(850,500) );
#ifdef __WXMSW__
	frame->SetIcon( wxICON( appicon ) );
#endif

	wxSnapLayout *lay = new wxSnapLayout(frame, wxID_ANY);

	
	wxPLPlotCtrl *plot = new wxPLPlotCtrl( lay, wxID_ANY, wxDefaultPosition, wxDefaultSize );
	//plot->SetBackgroundColour( *wxWHITE );
	plot->SetTitle( wxT("Demo Plot: using \\theta(x)=sin(x)^2, x_0=1\n\\zeta(x)=3\\dot sin^2(x)") );
	plot->SetClientSize( 400, 300 );
	wxFont font( *wxNORMAL_FONT );
	font.SetPointSize( 16 );
	plot->SetFont( font );
	
	lay->Add( plot, 400, 300 );
	lay->Add( new wxButton( lay, wxID_ANY, "EKJRLKEJWKR WJLKER WKEJRLKWJELR WE" ) );
	lay->Add( new wxButton( lay, wxID_ANY, "WE" ) );
	lay->Add( new wxCheckListBox( lay, wxID_ANY ) );
	lay->Add( new wxButton( lay, wxID_ANY, "%IN@)#*^^^^^$@#$_________________!!" ) );
	lay->Add( new wxCheckListBox( lay, wxID_ANY ) );

	frame->Show();

}


void TestPLPlot( wxWindow *parent )
{
	wxFrame *frame = new wxFrame( parent, wxID_ANY, wxT("wxPLPlotCtrl in \x01dc\x03AE\x03AA\x00C7\x00D6\x018C\x01dd"), wxDefaultPosition, wxSize(850,500) );
#ifdef __WXMSW__
	frame->SetIcon( wxICON( appicon ) );
#endif
		
	wxPLPlotCtrl *plot = new wxPLPlotCtrl( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize );
	//plot->SetBackgroundColour( *wxWHITE );
	plot->SetTitle( wxT("Demo Plot: using \\theta(x)=sin(x)^2, x_0=1\n\\zeta(x)=3\\dot sin^2(x)") );

	wxFont font( *wxNORMAL_FONT );
	font.SetPointSize( 16 );
	plot->SetFont( font );

		
	wxPLLabelAxis *mx = new wxPLLabelAxis( -1, 12, "Months of the year (\\Chi\\Psi)" );
	mx->ShowLabel( false );

	mx->Add( 0,  "Jan" );
	mx->Add( 1,  "Feb" );
	mx->Add( 2,  "March\nMarzo" );
	mx->Add( 3,  "Apr" );
	mx->Add( 4,  "May" );
	mx->Add( 5,  "June\nJunio" );
	mx->Add( 6,  "July" );
	mx->Add( 7,  "August" );
	mx->Add( 8,  "September" );
	mx->Add( 9,  "October" );
	mx->Add( 10, "November" );
	mx->Add( 11, "December\nDeciembre" );

	plot->SetXAxis2( mx );
	/*
	plot->SetYAxis1( new wxPLLinearAxis(-140, 150, wxT("y1 label\ntakes up 2 lines")) );
	plot->SetYAxis1( new wxPLLinearAxis(-11, -3, wxT("\\theta(x)")), wxPLPlotCtrl::PLOT_BOTTOM );
		
	*/
	//plot->SetScaleTextSize( true );

	plot->ShowGrid( true, true );
		
	plot->SetXAxis1( new wxPLLogAxis( 0.01, 100, "\\nu  (m^3/kg)" ) );		
//	plot->SetXAxis1( new wxPLTimeAxis( 4, 200 ) );

	std::vector< wxRealPoint > sine_data;
	std::vector< wxRealPoint > cosine_data;
	std::vector< wxRealPoint > tangent_data;
	for (double x = -6; x < 12; x+= 0.01)
	{
		sine_data.push_back( wxRealPoint( x, 3*sin( x )*sin( x ) ) );
		cosine_data.push_back( wxRealPoint( x/2, 2*cos( x/2 )*x ) );
		tangent_data.push_back( wxRealPoint( x, x*tan( x ) ) );
	}


	plot->AddPlot( new wxPLLinePlot( sine_data, "3\\dot sin^2(x)", "forest green", wxPLLinePlot::DOTTED ), 
		wxPLPlotCtrl::X_BOTTOM, 
		wxPLPlotCtrl::Y_LEFT, 
		wxPLPlotCtrl::PLOT_TOP);


	plot->GetXAxis1()->SetLabel( "Bottom X Axis has a great sequence of \\nu  values!" );
		

	plot->AddPlot( new wxPLLinePlot( cosine_data, "cos(\\Omega_\\alpha  )", *wxRED, wxPLLinePlot::DASHED ), 
		wxPLPlotCtrl::X_BOTTOM, 
		wxPLPlotCtrl::Y_LEFT,
		wxPLPlotCtrl::PLOT_TOP);
		
	wxPLLinePlot *lltan = new wxPLLinePlot( tangent_data, "\\beta\\dot tan(\\beta)", *wxBLUE, wxPLLinePlot::SOLID, 1, false );
	lltan->SetAntiAliasing( true );
	plot->AddPlot( lltan, 
		wxPLPlotCtrl::X_BOTTOM, 
		wxPLPlotCtrl::Y_LEFT,
		wxPLPlotCtrl::PLOT_BOTTOM);


	std::vector< wxRealPoint > pow_data;
	for (double i=0.01;i<20;i+=0.1)
		pow_data.push_back( wxRealPoint(i, pow(i,3)-0.02*pow(i,6) ) );
		

	plot->AddPlot( new wxPLLinePlot( pow_data, "i^3 -0.02\\dot i^6", *wxBLACK, wxPLLinePlot::SOLID ),
		wxPLPlotCtrl::X_BOTTOM,
		wxPLPlotCtrl::Y_LEFT,
		wxPLPlotCtrl::PLOT_TOP );



	plot->GetYAxis1()->SetLabel( "Pressure (kPa)" );
	plot->GetYAxis1()->SetColour( *wxRED );
	plot->GetYAxis1()->SetWorld( -20, 20 );
	//plot->SetFont( wxFont( 10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false ) );

	/*
	wxFrame *frame2 = new wxFrame( 0, wxID_ANY, wxT("GCDC vs DC"), wxDefaultPosition, wxSize( 850, 950 ) );
	TextLayoutDemo *tldemo = new TextLayoutDemo( frame2 );
	frame2->Show();
	*/

	wxLogWindow *log = new wxLogWindow( frame , "Log");
	wxLog::SetActiveTarget(log);
	log->Show();
		
	plot->SetAllowHighlighting( true );
				
	frame->Show();
}

#include "wex/dview/dvtimeseriesdataset.h"

void TestDView( wxWindow *parent )
{
	wxFrame *frame = new wxFrame( parent, wxID_ANY, "Test wxDView", wxDefaultPosition, wxSize(900,700) );
	wxDVPlotCtrl *dview = new wxDVPlotCtrl( frame, wxID_ANY );

	std::vector<double> data(8760);

	for (size_t i=0;i<8760;i++)
		data[i] = 123+i*100-i*i*0.01;
	dview->AddDataSet( new wxDVArrayDataSet( "curve 1", data ), "Group 1" );

	for (size_t i=0;i<8760;i++)
		data[i] = ::sin( i*0.001 ) * 10000;
	dview->AddDataSet( new wxDVArrayDataSet( "curve 2", data ), "Group 2");
	
	for (size_t i=0;i<8760;i++)
		data[i] = ::cos( i*0.01 ) * 15000;
	dview->AddDataSet( new wxDVArrayDataSet( "curve 3", data ), "Group 1");

	for (size_t i=0;i<8760;i++)
		data[i] = ::sin( i*0.1 ) * 5000;
	dview->AddDataSet( new wxDVArrayDataSet( "curve 4", data ), "Group 2");
	
	for (size_t i=0;i<8760;i++)
		data[i] = ::cos( i*0.0001 ) *2500;
	dview->AddDataSet( new wxDVArrayDataSet( "curve 5", data ), "Group 2");

	frame->Show();
}

#include <wex/numeric.h>
#include <wex/exttext.h>
enum { ID_NUMERIC = wxID_HIGHEST+121, ID_EXTTEXT, ID_CLEAR, ID_MENU_TEST,
ID_MENU_FIRST, ID_MENU_LAST=ID_MENU_FIRST+40};
class NumericTest : public wxFrame
{
	int m_counter;
	wxNumericCtrl *m_num;
	wxExtTextCtrl *m_txt;
	wxTextCtrl *m_log;
	wxButton *m_button;
	wxMetroNotebook *m_nb;
public:
	NumericTest() : wxFrame( NULL, wxID_ANY, "Numeric Test", wxDefaultPosition, wxSize(700,700) )
	{
		wxPanel *panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

		m_counter = 0;
		m_num = new wxNumericCtrl( panel, ID_NUMERIC );
		m_txt = new wxExtTextCtrl( panel, ID_EXTTEXT );

		m_log = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );

		m_button = new wxButton( panel, ID_MENU_TEST, "Test popup" );

		wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL );
		sizer->Add( m_num, 0, wxALL|wxEXPAND, 10 );
		sizer->Add( m_txt, 0, wxALL|wxEXPAND, 10 );
		sizer->AddStretchSpacer();
		sizer->Add( new wxButton( panel, ID_CLEAR, "Clear" ), 0, wxALL|wxEXPAND, 10 );
		sizer->Add( m_button );

		wxBoxSizer *main = new wxBoxSizer( wxVERTICAL );
		main->Add( sizer, 0, wxALL|wxEXPAND, 10 );
		main->Add( m_log, 1, wxALL|wxEXPAND, 10 );

		m_nb = new wxMetroNotebook( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxMT_LIGHTTHEME );
		m_nb->AddPage( new wxPanel( m_nb ), "Page 1", false, true );
		m_nb->AddPage( new wxPanel( m_nb ), "Page 2" );
		m_nb->AddPage( new wxPanel( m_nb ), "Page 3", false, true );
		m_nb->AddPage( new wxPanel( m_nb ), "Page 4" );

		main->Add( m_nb, 1, wxALL|wxEXPAND, 0 );

		panel->SetSizer( main );
	}

	void OnNumeric( wxCommandEvent &evt )
	{
		m_log->AppendText( wxString::Format("%d --> numeric changed %.6lf\n", ++m_counter, m_num->Value()) );
	}

	void OnExtText( wxCommandEvent &evt )
	{
		m_log->AppendText( wxString::Format("%d --> exttext changed\n", ++m_counter) );
	}

	void OnClear( wxCommandEvent & )
	{
		m_log->Clear();
	}

	void OnMenu( wxCommandEvent &evt )
	{
		m_log->AppendText( wxString::Format("popup menu item clicked: %d\n", evt.GetId() ) );
	}

	void OnMenuTest( wxCommandEvent &evt )
	{
		m_log->AppendText( "menu popup initiated\n" );
		wxMetroPopupMenu menu;
	//	menu.SetFont( wxMetroTheme::Font( wxMT_LIGHT, 20 ) );

		int id = ID_MENU_FIRST;
		menu.Append( id++, "First item\tF2" );
		menu.Append( id++, "Second item\tCtrl-O" );
		menu.Append( id++, "Third item" );
		menu.Append( id++, "Fourth item" );
		menu.AppendSeparator();
		menu.Append( id++, "Exit" );
		menu.Popup( this );
	}

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE( NumericTest, wxFrame )
	EVT_NUMERIC( ID_NUMERIC, NumericTest::OnNumeric )
	EVT_TEXT_ENTER( ID_EXTTEXT, NumericTest::OnExtText )
	EVT_BUTTON( ID_CLEAR, NumericTest::OnClear )
	EVT_BUTTON( ID_MENU_TEST, NumericTest::OnMenuTest )
	EVT_MENU_RANGE( ID_MENU_FIRST, ID_MENU_LAST, NumericTest::OnMenu )
END_EVENT_TABLE()


class MyApp : public wxApp
{
	wxLocale m_locale;
public:
	bool OnInit()
	{
		if ( !wxApp::OnInit() )
			return false;
		
		wxInitAllImageHandlers();
		
		m_locale.Init();
	
		wxLogWindow *log = new wxLogWindow( 0 , "Log");
		wxLog::SetActiveTarget(log);
		log->Show();

		//wxFrame *frame = new NumericTest();
		//frame->Show();
		

		//TestPLPlot( 0 );

		//TestSnapLayout( 0 );

		TestDVSelectionCtrl();


		/*
		wxFrame *frame = new wxFrame(NULL, wxID_ANY, "Test LKEdit", wxDefaultPosition, wxSize(600,400) );
		new wxLKScriptCtrl(frame, wxID_ANY );
		frame->Show();
		*/

		/*
		
		wxFrame *frm = new wxFrame(NULL, wxID_ANY, "SchedCtrl", wxDefaultPosition, wxSize(1100,700));
		frm->SetBackgroundColour( *wxWHITE );
		
		wxBoxSizer *tools = new wxBoxSizer( wxHORIZONTAL );
		tools->Add( new wxMetroButton( frm, wxID_ANY, wxEmptyString, wxBITMAP_PNG_FROM_DATA( demo_bitmap ), wxDefaultPosition, wxDefaultSize ), 0, wxALL|wxEXPAND, 0 );
		tools->Add( new wxMetroButton( frm, wxID_ANY, "New", wxBITMAP_PNG_FROM_DATA( cirplus ), wxDefaultPosition, wxDefaultSize), 0, wxALL|wxEXPAND, 0 );
		wxMetroTabList *tabs = new wxMetroTabList( frm, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxMT_MENUBUTTONS );
		tabs->Append( "photovoltaic #1" );
		tabs->Append( "solar water" );
		tabs->Append( "power tower steam" );
		tools->Add( tabs, 1, wxALL|wxEXPAND, 0 );		
		tools->Add( new wxMetroButton( frm, wxID_ANY, wxEmptyString, wxBITMAP_PNG_FROM_DATA(qmark), wxDefaultPosition, wxDefaultSize), 0, wxALL|wxEXPAND, 0 );
		//tools->Add( new wxMetroButton( frm, wxID_ANY, wxEmptyString, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxMB_DOWNARROW), 0, wxALL|wxEXPAND, 0 );
		
		wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );
		sizer->Add( tools, 0, wxALL|wxEXPAND, 0 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Start", wxBITMAP_PNG_FROM_DATA( demo_bitmap ), wxDefaultPosition, wxDefaultSize, wxMB_RIGHTARROW), 0, wxALL, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Stretched Start", wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxMB_RIGHTARROW), 0, wxALL|wxEXPAND, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Test button"), 0, wxALL, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Popup menu", wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxMB_DOWNARROW), 0, wxALL, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Left align label", wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxMB_ALIGNLEFT), 0, wxEXPAND|wxALL, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, "Left align arrow", wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxMB_ALIGNLEFT|wxMB_RIGHTARROW), 0, wxEXPAND|wxALL, 3 );
		sizer->Add( new wxMetroButton( frm, wxID_ANY, wxEmptyString, wxBITMAP_PNG_FROM_DATA( demo_bitmap ), wxDefaultPosition, wxDefaultSize), 0, wxALL, 3 );
		
		
		wxMetroNotebook *nb = new wxMetroNotebook( frm, wxID_ANY, wxDefaultPosition, wxDefaultSize );
		nb->AddPage( new wxPanel( nb ), "Case 1: PV" );
		nb->AddPage( new wxPanel( nb ), "Case 2: PV+debt" );
		nb->AddPage( new wxPanel( nb ), "Wind system" );
		nb->AddPage( new wxPanel( nb ), "solar water heat" );
		sizer->Add( nb, 1, wxALL|wxEXPAND, 0 );
		nb = new wxMetroNotebook( frm, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxMT_LIGHTTHEME );
		nb->AddPage( new wxPanel( nb ), "Base Case" );
		nb->AddPage( new wxPanel( nb ), "Parametrics" );
		nb->AddPage( new wxPanel( nb ), "Sensitivities" );
		nb->AddPage( new wxPanel( nb ), "Statistics" );
		nb->AddPage( new wxPanel( nb ), "Scripting" );
		sizer->Add( nb, 1, wxALL|wxEXPAND, 0 );

		//wxDiurnalPeriodCtrl *sch = new wxDiurnalPeriodCtrl( frm, wxID_ANY );
		//sch->SetupTOUGrid();		
		//sizer->Add( sch, 1, wxALL|wxEXPAND, 5 );

		frm->SetSizer( sizer );
		frm->Show();
		
		*/


/*		
		wxUIObjectTypeProvider::RegisterBuiltinTypes();
		wxUIFormData *form = new wxUIFormData;
		wxFrame *frm = new wxFrame( 0, wxID_ANY, "Form Editor", wxDefaultPosition, wxSize(900, 600) );
		wxUIFormDesigner *fd = new wxUIFormDesigner( frm, wxID_ANY );

		wxUIPropertyEditor *pe = new wxUIPropertyEditor(frm, wxID_ANY );
		wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add( pe, 1, wxALL|wxEXPAND, 0 );
		sizer->Add( fd, 5, wxALL|wxEXPAND, 0 );
		frm->SetSizer(sizer);

		fd->SetFormData( form );
		fd->SetPropertyEditor( pe );
		frm->Show();*/

		
	//	TestPLPlot( 0 );
		
	/*
		wxChar sep = ',';
		bool use_thousep = wxNumberFormatter::GetThousandsSeparatorIfUsed(&sep);
		wxMessageBox( m_locale.GetLocale() + "\n" + wxString::Format( "thousep? %d sep=%c\n\n", use_thousep ? 1:0, (char)sep)
			+ wxNumberFormatter::ToString( 12490589.02, 2, wxNumberFormatter::Style_WithThousandsSep ) );

			

		
		
		wxFrame *top = new wxFrame(NULL, wxID_ANY, "CSV Read Test", wxDefaultPosition, wxSize(500,500));
		
		wxDiurnalPeriodCtrl *sched = new wxDiurnalPeriodCtrl( top, wxID_ANY );
		sched->SetupTOUGrid();

		wxGrid *grid = new wxGrid( top, wxID_ANY );
		
		wxCSVData csv;
		wxStopWatch sw;
		bool ok = csv.ReadFile( "c:/Users/adobos/Desktop/csv_test.csv" );
		int msec = sw.Time();
		csv.WriteFile("c:/Users/adobos/Desktop/csv_test2.csv");
		int nr = (int)csv.NumRows()+1;
		int nc = (int)csv.NumCols()+1;
		top->SetTitle( wxString::Format("CSVRead: (%d ms) %d %s [%d x %d]", msec, csv.GetErrorLine(), ok?"ok":"fail", nr, nc) );

		if (nr > 0 && nc > 0)
		{
			grid->CreateGrid( nr, nc );
			for ( size_t r = 0; r < nr; r++ )
				for ( size_t c = 0; c < nc; c++ )
					grid->SetCellValue( r, c, csv(r,c) );
		}
*/
		
		return true;
	}
};

IMPLEMENT_APP( MyApp );
