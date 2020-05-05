///-----------------------------------------------------------------
///
/// @file      parkingFrm.cpp
/// @author    Moshe Adique, Aaron Mandap, Victor Tirona
/// Created:   08/10/2019 11:55:44 PM
/// @section   DESCRIPTION
///            parkingFrm class implementation
///
///------------------------------------------------------------------

#include "parkingFrm.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// parkingFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(parkingFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(parkingFrm::OnClose)
	EVT_ACTIVATE(parkingFrm::parkingFrmActivate)
	EVT_BUTTON(ID_WXBUTTON6,parkingFrm::WxButton6Click0)
	
	EVT_TEXT(ID_WXEDIT1,parkingFrm::WxEdit1Updated)
	EVT_BUTTON(ID_WXBUTTON2,parkingFrm::WxButton2Click)
	
	EVT_RICHTEXT_BUFFER_RESET(ID_EDT_BROWSE,parkingFrm::edt_browseBufferReset)
	EVT_BUTTON(ID_WXBUTTON1,parkingFrm::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

parkingFrm::parkingFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

parkingFrm::~parkingFrm()
{
}

void parkingFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	WxMessageDialog1 =  new wxMessageDialog(this, _(""), _("Message box"));

	dlg_browse =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);

	WxButton6 = new wxButton(this, ID_WXBUTTON6, _("All in One"), wxPoint(443, 639), wxSize(502, 25), 0, wxDefaultValidator, _("WxButton6"));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _(""), wxPoint(356, 369), wxSize(598, 256), wxTE_MULTILINE, wxDefaultValidator, _("WxEdit1"));

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("Get Ref"), wxPoint(44, 638), wxSize(178, 25), 0, wxDefaultValidator, _("WxButton2"));

	WxStaticBitmap1 = new wxStaticBitmap(this, ID_WXSTATICBITMAP1, wxNullBitmap, wxPoint(44, 359), wxSize(300, 270) );

	BmpOutput = new wxStaticBitmap(this, ID_BMPOUTPUT, wxNullBitmap, wxPoint(356, 73), wxSize(600, 290) );

	BmpInput = new wxStaticBitmap(this, ID_BMPINPUT, wxNullBitmap, wxPoint(44, 74), wxSize(300, 270) );

	edt_browse = new wxRichTextCtrl(this, ID_EDT_BROWSE, _(""), wxPoint(47, 25), wxSize(830, 25), 0, wxDefaultValidator, _("edt_browse"));
	edt_browse->SetMaxLength(0);
	edt_browse->AppendText(_("edt_browse"));
	edt_browse->SetFocus();
	edt_browse->SetInsertionPointEnd();

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Get Input"), wxPoint(232, 639), wxSize(203, 25), 0, wxDefaultValidator, _("WxButton1"));

	SetTitle(_("parking"));
	SetIcon(wxNullIcon);
	SetSize(10,2,996,713);
	Center();
	
	////GUI Items Creation End
}

void parkingFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

/*
 * WxButton1Click
 */
 
 void parkingFrm::WxEdit1Updated(wxCommandEvent& event)
{
	// insert your code here
}

wxImage imageAlignment (wxImage refImg, wxImage inpImg)
{
  wxImage outImg = refImg;
  int halfShift=5;
  int refImgHeight = refImg.GetHeight();
  int refImgWidth = refImg.GetWidth();
  int product = refImgHeight*refImgWidth*255;
  int minSD = 3*product*product;
  int minx;
  int miny;
  for (int x=-halfShift; x<halfShift;x++)
  {
    for (int y=-halfShift; y<halfShift;y++)
    {
      int squareDiff=0;
      int compR=0;
      int compG=0;
      int compB=0;
      for (int i=0; i<refImg.GetWidth(); i++)
      {          
        for (int j=0; j<refImg.GetHeight(); j++)
        {
          if ((refImg.GetWidth()>=(i+x)) && (refImg.GetHeight()>=(j+y)) && ((i+x)>=0) && ((j+y)>=0))
          {
            unsigned char r = refImg.GetRed(i,j);
            unsigned char g = refImg.GetGreen(i,j);
            unsigned char b = refImg.GetBlue(i,j);
            unsigned char r2 = inpImg.GetRed(i+x,j+y);
            unsigned char g2 = inpImg.GetGreen(i+x,j+y);
            unsigned char b2 = inpImg.GetBlue(i+x,j+y);   
            compR=compR+(r-r2)*(r-r2);
            compG=compG+(g-g2)*(g-g2);
            compB=compB+(b-b2)*(b-b2);
            squareDiff=squareDiff+compR+compG+compB;
          }
        }
      }
      if (squareDiff<minSD)
      {
        minSD=squareDiff;
        minx=x;
        miny=y;
      }
    }
  }
    
  for (int i=0; i<refImg.GetWidth(); i++)
  {          
    for (int j=0; j<refImg.GetHeight(); j++)
    {
      unsigned char r = inpImg.GetRed(i-minx,j-miny);
      unsigned char g = inpImg.GetGreen(i-minx,j-miny);
      unsigned char b = inpImg.GetBlue(i-minx,j-miny);
      outImg.SetRGB(i,j,r,g,b);
    }
  }
  return outImg;
}

/*wxImage greyscale(wxImage img)
{ 
  for (int i = 0; i < img.GetWidth(); i++)
  {
    for (int j = 0; j < img.GetHeight(); j++)
    {
      unsigned char r = img.GetRed(i,j);
      unsigned char g = img.GetGreen(i,j);
      unsigned char b = img.GetBlue(i,j);
      unsigned char gray = (r*299 + g*587 + b*114)/1000;
      img.SetRGB(i,j,gray,gray,gray); 
    }
  }
  return img;
}*/

wxImage binarization(wxImage img)
{ 
  //Histogram 
  double histogram[256] = {};
  unsigned char value;
  
  //Store histogram values
  for (int i=0; i<img.GetWidth(); i++)
  {
    for (int j=0; j<img.GetHeight(); j++)
    {
      unsigned char r = img.GetRed(i,j);
      unsigned char g = img.GetGreen(i,j);
      unsigned char b = img.GetBlue(i,j);
      unsigned char value = (r*306 + g*601 + b*117)>>10;
      histogram[value] +=1;
    }  
  }
  
  //Sum of all frequencies times the possible threshold
  double sum = 0;
  for (int t=0 ; t<256 ; t++)
  {
    sum += t*histogram[t];
  }

  //Sum all the frequencies
  double totalFreq = 0;
  for (int t=0 ; t<256 ; t++)
  {
    totalFreq += histogram[t];
  }

  double sumB = 0;   //Sum of frequencies times possible threshold until the background
  double bgWeight = 0; //Background weight
  double fgWeight = 0; //Background foreground
    
  double totalBg = 0; //Background weight
  double totalFg = 0; //Background foreground

  double maxVar = 0;
  double threshold = 0;

  for (int t=0 ; t<256 ; t++)
  {
    totalBg += histogram[t];
    if (totalBg == 0) continue;
  
    //Subtract background frequency from the total 
    // frequency to get the foreground frequency
    totalFg = totalFreq - totalBg;
  
    //Sum of all frequencies times the possible 
    // threshold until the current threshold
    sumB += t*histogram[t];
  
    double bgMean = sumB / totalBg;          // Mean Background
    double fgMean = (sum - sumB) / totalFg;  // Mean Foreground
      
    bgWeight = totalBg / totalFreq;
    fgWeight = totalFg / totalFreq;
  
    // Calculate Between Class Variance
    double bcVar = bgWeight * fgWeight * 
      (bgMean - fgMean) * (bgMean - fgMean);
  
    // Check if new maximum found
    if (bcVar > maxVar)
    {
      maxVar = bcVar;
      threshold = t;
    }
  }
  
  //Set all pixels below threshold to white, otherwise set it to black
  for (int i=0; i<img.GetWidth(); i++)
  {
    for (int j=0; j<img.GetHeight(); j++)
    {
      unsigned char value = img.GetRed(i,j);
      if(value < threshold)
      {
        img.SetRGB(i,j,0,0,0);    
      }
      else
      {
        img.SetRGB(i,j,255,255,255);  
      }
    }
  }
  
  return img;
}//end binarization  

vector<int> slotDetection (wxImage refImg, wxImage inpImg, wxImage &output)
{
  //inpImg = imageAlignment(refImg, inpImg);
  unsigned char value;
  vector<int> verticals;
  vector<int> horizontals;
  int refImgWidth = refImg.GetWidth();
  int refImgHeight = refImg.GetHeight();
  int verticalCondition = refImgHeight*3/4;
  int pixel = 0;
  int line = 0;
  int state = 0;
  
  horizontals.push_back(0);
  //binarize Image
  refImg = binarization(refImg);
  
  //find vertical lines
  for (int i=0; i<refImgWidth; i++)
  {
    for (int j=0; j<refImgHeight; j++)
    {
      value = refImg.GetRed(i,j);
      if (state == 0)
      {
        if (value == 255)
        {
          pixel++;
        }
      }
      else
      {
        if (value == 0)
        {
          pixel++;
        }
      }
    }
    if (pixel > verticalCondition)
    {
      line++;
    }
    if (line > 4)
    {
      verticals.push_back(i-4);
      line = 0;
      if (state == 0)
      {
        state = 1;
      }
      else if (state == 1)
      {
        state = 0;
      }
    }
    pixel = 0;
  }
  
  //find horizontal lines
  line = 0;
  int horizontalCondition = (verticals[2]-verticals[1])*3/4;
  for (int j=0; j<refImgHeight; j++)
  {
    for (int i=verticals[1]; i<verticals[2]; i++)
    {
      value = refImg.GetRed(i,j);
      if (state == 0)
      {
        if (value == 255)
        {
          pixel++;
        }
      }
      else
      {
        if (value == 0)
        {
          pixel++;
        }
      }
    }
    if (pixel > horizontalCondition)
    {
      line++;
    }
    if (line > 4)
    {
      horizontals.push_back(j-4);
      line = 0;
      if (state == 0)
      {
        state = 1;
      }
      else if (state == 1)
      {
        state = 0;
      }
    }
    pixel = 0;
  }
  horizontals.push_back(refImgHeight-1);
  
  //check of individual slots
  inpImg = binarization(inpImg);
  vector<int> slots;
  int slotNumber = (verticals.size()-2)/2;
  float countW = 0;
  float countB = 0;
  float ratio = 0;
  int topBorder, bottomBorder, leftBorder, rightBorder;
  for (int a=0; a<2; a++)
  {
    topBorder = horizontals[2*a];
    bottomBorder = horizontals[2*a+1];
    for (int b=1; b<=slotNumber; b++)
    {
      leftBorder = verticals[2*b-1];
      rightBorder = verticals[2*b];
      for (int i=leftBorder; i<rightBorder; i++)
      {
        for (int j=topBorder; j<bottomBorder; j++)
        {
          if(inpImg.GetRed(i,j) == 255)
          {
            countW++;
          }
          else
          {
            countB++;
          }
        }
      }
      ratio = countW/(countW+countB);
      if(ratio >= .3)
      {
        slots.push_back(1);
      }
      else
      {
        slots.push_back(0);
      }
      countW=0;
      countB=0;
      ratio = 0;
    }
  }
  
  for (unsigned int a=0; a<horizontals.size(); a++)
  {
    for(int b=0; b<inpImg.GetWidth(); b++)
    {
      inpImg.SetRGB(b,horizontals[a],255,0,0);
    }
  }
  
  for (unsigned int a=0; a<verticals.size(); a++)
  {
    for(int b=0; b<inpImg.GetHeight(); b++)
    {
      inpImg.SetRGB(verticals[a],b,255,0,0);
    }
  }
  output = inpImg;
  return slots;
}


void parkingFrm::WxButton2Click(wxCommandEvent& event)
{
	dlg_browse -> ShowModal();
  
  if (dlg_browse -> GetPath().IsEmpty())
  {
    return;
  }                       
  
  edt_browse -> SetValue(dlg_browse -> GetPath());
  refImg.LoadFile(dlg_browse -> GetPath(), wxBITMAP_TYPE_ANY);
  int h = refImg.GetHeight();
  int w = refImg.GetWidth();
  
  if (h != 270 && w != 300) {
    wxImage buff = refImg;
    WxStaticBitmap1 -> SetBitmap(buff.Scale(300, 270));
  }
  else
    WxStaticBitmap1 -> SetBitmap(refImg);
}

void parkingFrm::WxButton1Click(wxCommandEvent& event)
{
	// insert your code here
  dlg_browse -> ShowModal();
  
  if (dlg_browse -> GetPath().IsEmpty())
  {
    return;
  }                       
  
  edt_browse -> SetValue(dlg_browse -> GetPath());
  inpImg.LoadFile(dlg_browse -> GetPath(), wxBITMAP_TYPE_ANY);
  
  int h = inpImg.GetHeight();
  int w = inpImg.GetWidth();
  
  if (h != 270 && w != 300) {
    wxImage buff = inpImg;
    BmpInput -> SetBitmap(buff.Scale(300, 270));
  }
  else {
    BmpInput -> SetBitmap(inpImg);
  }
}




/*
 * edt_browseBufferReset
 */
void parkingFrm::edt_browseBufferReset(wxRichTextEvent& event)
{
	// insert your code here
}

/*
 * parkingFrmActivate
 */
void parkingFrm::parkingFrmActivate(wxActivateEvent& event)
{
	// insert your code here
}

/*
 * WxButton2Click
 */


/*
 * WxButton4Click
 */
void parkingFrm::WxButton4Click(wxCommandEvent& event)
{
	// insert your code here
	
	output = binarization(inpImg);
  if (output.GetHeight() != 400 && output.GetWidth() != 600){
    wxImage buffOut = output;
    BmpOutput -> SetBitmap(buffOut.Scale(600, 400));
  }
  else
    BmpOutput -> SetBitmap(output);
}
/*
 * WxButton3Click
 */
void parkingFrm::WxButton3Click(wxCommandEvent& event)
{
	// insert your code here
  output = imageAlignment(refImg, inpImg);
  if (output.GetHeight() != 250 && output.GetWidth() != 300){
    wxImage buffOut = output;
    BmpOutput -> SetBitmap(buffOut.Scale(300, 250));
  }
  else
    BmpOutput -> SetBitmap(output);
}




/*
 * WxButton5Click0
 */
void parkingFrm::WxButton5Click0(wxCommandEvent& event)
{
	// insert your code here
	//output = slotDetection(inpImg, refImg);
  if (output.GetHeight() != 290 && output.GetWidth() != 600){
    wxImage buffOut = output;
    BmpOutput -> SetBitmap(buffOut.Scale(600, 290));
  }
  else
    BmpOutput -> SetBitmap(output);
    
  WxEdit1 -> SetValue("HI");
}

/*
 * WxRichTextCtrl1BufferReset
 */
void parkingFrm::WxRichTextCtrl1BufferReset(wxRichTextEvent& event)
{
	// insert your code here
}

/*
 * WxEdit1Updated
 */

/*
 * WxButton6Click0
 */
void parkingFrm::WxButton6Click0(wxCommandEvent& event)
{
  // insert your code here
  vector<int> slots;
  wxImage output;
  slots = slotDetection(refImg, inpImg, output);

  if (output.GetHeight() != 290 && output.GetWidth() != 600){
    wxImage buffOut = inpImg;
    BmpOutput -> SetBitmap(buffOut.Scale(600, 290));
  }
  else
    BmpOutput -> SetBitmap(output);
  int size = slots.size();
  int halfSize = (size+1)/2;
  int c, e, d, f;
  wxString b, row, column;
  WxEdit1 -> SetValue("");
  for (int i=0; i<2; i++)
  {
    d = i+1;
    row = wxString::Format(wxT("%d"), (int)d);
    for (int a=0; a<halfSize; a++)
    {
      e = i*halfSize+a;
      c = e+1;
      f = a+1;
      column = wxString::Format(wxT("%d"), (int)f);
      if (slots[e] == 0)
      {
        b = wxString::Format(wxT("%d"), (int)c);
        WxEdit1 -> AppendText("SLOT ");
        WxEdit1 -> AppendText(b);
        WxEdit1 -> AppendText(" VACANT         ROW ");
        WxEdit1 -> AppendText(row);
        WxEdit1 -> AppendText("   COLUMN ");
        WxEdit1 -> AppendText(column);
        WxEdit1 -> AppendText("\n");
      }
      else if (slots[e] == 1)
      {
        b = wxString::Format(wxT("%d"), (int)c);
        WxEdit1 -> AppendText("SLOT ");
        WxEdit1 -> AppendText(b);
        WxEdit1 -> AppendText(" OCCUPIED     ROW ");
        WxEdit1 -> AppendText(row);
        WxEdit1 -> AppendText("   COLUMN ");
        WxEdit1 -> AppendText(column);
        WxEdit1 -> AppendText("\n");
      }
    }
  }
  
  /*
  if (slots[0] == 1)
    WxEdit1 -> SetValue("OCCUPIED");
  else if (slots[0] == 0)
    WxEdit1 -> SetValue("VACANT");
  if (slots[1] == 1)
    WxEdit2 -> SetValue("OCCUPIED");
  else if (slots[1] == 0)
    WxEdit2 -> SetValue("VACANT");
  if (slots[2] == 1)
    WxEdit3 -> SetValue("OCCUPIED");
  else if (slots[2] == 0)
    WxEdit3 -> SetValue("VACANT");
  if (slots[3] == 1)
    WxEdit4 -> SetValue("OCCUPIED");
  else if (slots[3] == 0)
    WxEdit4 -> SetValue("VACANT");
  if (slots[4] == 1)
    WxEdit5 -> SetValue("OCCUPIED");
  else if (slots[4] == 0)
    WxEdit5 -> SetValue("VACANT");
  if (slots[5] == 1)
    WxEdit6 -> SetValue("OCCUPIED");
  else if (slots[5] == 0)
    WxEdit6 -> SetValue("VACANT");
  if (slots[6] == 1)
    WxEdit7 -> SetValue("OCCUPIED");
  else if (slots[6] == 0)
    WxEdit7 -> SetValue("VACANT");
  if (slots[7] == 1)
    WxEdit8 -> SetValue("OCCUPIED");
  else if (slots[7] == 0)
    WxEdit8 -> SetValue("VACANT"); */
}
