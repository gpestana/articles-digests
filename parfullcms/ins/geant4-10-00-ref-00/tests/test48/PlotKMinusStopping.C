#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

#include <math.h>
#include <vector>

#include "Rtypes.h"
#include "TROOT.h"
#include "TRint.h"
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TRefArray.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TLegend.h"

// Note that BertiniPreCo doesn't make much sense for H
// that's why there're 2 models here
//
const int NModelsMesons=2; 
std::string ModelsMesons[2] = { "Bertini", "BertiniPreCo" };

//int         ColorModel[4]    = { 1, 2, 6, 3 };
//int         SymbModel[4]     = { 20, 29, 21, 8 };
int         ColorModel[2]    = {  6, 3 };
int         SymbModel[2]     = { 21, 8 };

// K- beam business - exp. data
const int NPointsKMinus_Pi0Energy = 82;
float Pi0Energy[82], Pi0EnergyStat[82];

const int NDModes = 7;
float KaonicHyBR[7] = { 0.067, 0.273, 0.178, 0.430, 0.0004, 0.0028, 0.273 } ;
int ModeID[7] = { 1, 2, 3, 4, 7, 8, 9 };
std::string Labels[7] = { "#Lambda #pi^{0}", "#Lambda #gamma #pi^{0}", "#Sigma^{+} #pi^{-}", "#Sigma^{-} #pi^{+}", "#Sigma^{0} #gamma", "#Lambda #gamma", "#Sigma^{0} #pi^{0}" };



const int NVersions = 2;
//int ColorVersion[4] = { kBlack, kRed, kGreen, kMagenta };
int ColorVersion[3] = { kGreen, kRed, kBlack };

std::string Versions[2] = { "geant4-09-06-b01", "geant4-09-06-p01" };
 
void readKMinusPi0Energy()
{

   std::string fname = "./kminus/pi0_energy_larson.dat";
   std::cout << "Reads data from file " << fname << "\n";
   ifstream infile;
   infile.open(fname.c_str());
      
   for ( int i=0; i<NPointsKMinus_Pi0Energy; i++ )
   {
   
      infile >> Pi0Energy[i] >> Pi0EnergyStat[i] ;
      // rescale for (approx.) stat
      Pi0EnergyStat[i] /= 1028571;
   
   }
   
   infile.close();
   
   return;

}

void drawKMinusBertiniForCTest( std::string target="H" )
{

   std::string histofile = "kminus" + target + "Bertini.root";
   TFile* f = new TFile( histofile.c_str() );
   TH1F* hi = (TH1F*)f->Get( "Topology" );
   hi->SetStats(0);
   hi->SetLineColor(kMagenta);
   hi->SetLineWidth(2);
   
   hi->Draw();
      
   TH1F* h = new TH1F("h", " ", 10, 0, 10. );

   for ( int i=0; i<NDModes; i++ )
   {
	 float val = (float)ModeID[i] + 0.5;
	 h->Fill( val, KaonicHyBR[i] );
	 h->GetXaxis()->SetBinLabel( ModeID[i], Labels[i].c_str() );
   }
   h->SetStats(0);
   h->SetMarkerStyle(22);
   h->SetMarkerColor(4);
   h->SetMarkerSize(1.6);
   h->Draw("psame");
  
   return;

}

void plotKMinus2( std::string target )
{

   TCanvas* myc = new TCanvas("myc1","",1200,600);
   myc->Divide(2,1);
   
   myc->cd(1);
   gPad->SetLeftMargin(0.15);
   gPad->SetLogy();
   drawKMinus( target, "Topology" );
   
   myc->cd(2);
   gPad->SetLeftMargin(0.15);
   gPad->SetLogy();
   drawKMinus( target, "EnergyPi0" );
   
   myc->cd();

   return;

}

void plotKMinusAll( std::string target )
{
   
   TCanvas* myc1 = new TCanvas("myc1","",1200,600);
   // myc1->Divide(3,2);
   TCanvas* myc2 = new TCanvas("myc2","",1200,600);

   if ( target =="H" || target =="He" )
   {
      //myc1->cd();
      //myc1->Divide( 3, 1 );    
      myc1->Divide(3,2);
      myc1->cd(1); gPad->SetLogy(1);
      drawKMinus( target, "NSecondaries" );
      myc1->cd(2); gPad->SetLogy(1);
      drawKMinus( target, "Topology" );
      myc1->cd(3); gPad->SetLogy(1);
      drawKMinus( target, "PartTypeMult" );  
      //myc2->cd(); 
      //myc2->Divide( 3, 1 );   
      // myc2->cd(1); 
      myc1->cd(4); 
      gPad->SetLogy(1);
      drawKMinus( target, "EnergyPi0" );
      // myc2->cd(2); 
      myc1->cd(5); 
      gPad->SetLogy(1);
      drawKMinus( target, "EnergyPhoton" );
      // myc2->cd(3); 
      myc1->cd(6); 
      gPad->SetLogy(1);
      drawKMinus( target, "EnergyChargedPions" );
   }
   else
   {
      myc1->cd();
      myc1->Divide( 2, 1 );
      myc1->cd(1); gPad->SetLogy(1);
      drawKMinus( target, "NSecondaries" );
      myc1->cd(2); gPad->SetLogy(1);
      drawKMinus( target, "PartTypeMult" );  
      myc2->cd(); 
      myc2->Divide( 2, 1 );   
      myc2->cd(1); gPad->SetLogy(1);
      drawKMinus( target, "EnergyPi0" );
      myc2->cd(2); gPad->SetLogy(1);
      drawKMinus( target, "EnergyChargedPions" );
   }
   
   return;

}

void drawKMinus( std::string target, std::string histo )
{

   TH1F** hi;
      
   double ymin = 10000.; // something big... don't know if I can use FLT_MAX
   double ymax = -1. ;
   int NCounts;
   if ( target == "H" )
   {
      NCounts = NModelsMesons-1;
      hi = new TH1F*[NModelsMesons-1];
   }
   else
   {
      NCounts = NModelsMesons;
      hi = new TH1F*[NModelsMesons];
   }
   for ( int m=0; m<NCounts; m++ )
   {
      std::string histofile = "kminus" + target + ModelsMesons[m];
      histofile += ".root";
      TFile* f = new TFile( histofile.c_str() );
      hi[m] = (TH1F*)f->Get( histo.c_str() );
      // turn off the stats pad; use this space to draw color codes, etc.
      hi[m]->SetStats(0);
      hi[m]->SetLineColor(ColorModel[m]);
      hi[m]->SetLineWidth(2);
      if ( histo == "EnergyPi0" )
      {
         hi[m]->GetXaxis()->SetTitle("Total energy of secondary pi0 (MeV)" );
         hi[m]->GetYaxis()->SetTitle("dN / dE (MeV)^{-1} / NEvents");
	 hi[m]->GetYaxis()->SetTitleOffset(1.5);
      }
      else
      {
         hi[m]->GetXaxis()->SetTitle( histo.c_str() );
         // hi[m]->GetYaxis()->SetTitle("Number of neutrons per MeV");
      }
      int nx = hi[m]->GetNbinsX();
      for (int k=1; k <= nx; k++) {
	double yy = hi[m]->GetBinContent(k);
	if ( yy > ymax ) ymax = yy;
	if ( yy < ymin && yy > 0. ) ymin = yy;
      }
      if ( m == 0 ) hi[m]->Draw();
      else hi[m]->Draw("same");
   }
   
   TLegend* leg = new TLegend(0.6, 0.70, 0.9, 0.9);
   
   for ( int m=0; m<NCounts; m++ )
   {      
      if ( histo == "EnergyPi0" ) 
      {
         hi[m]->GetYaxis()->SetRangeUser( 0.000001, ymax*3. );
      }
      else
      {
         hi[m]->GetYaxis()->SetRangeUser(ymin,ymax*3.); // hi[m]->SetTitle("");
      }
      leg->AddEntry( hi[m], ModelsMesons[m].c_str(), "L" );
   }
   
   if ( histo == "EnergyPi0" && target == "H" )
   {
      readKMinusPi0Energy();
      TGraph* gr = new TGraph( NPointsKMinus_Pi0Energy, Pi0Energy, Pi0EnergyStat );
      gr->SetMarkerColor(4); // blue, alt. would be kBlue
      gr->SetMarkerStyle(22); // solid triangle
      gr->SetMarkerSize(1.6);
      gr->Draw("p");
      leg->AddEntry( gr, "exp.data", "p" );
   }
   
   if ( histo == "Topology" && target == "H" )
   {
      TH1F* h = new TH1F("h", " ", 10, 0, 10. );

      for ( int i=0; i<NDModes; i++ )
      {
	 float val = (float)ModeID[i] + 0.5;
	 h->Fill( val, KaonicHyBR[i] );
	 h->GetXaxis()->SetBinLabel( ModeID[i], Labels[i].c_str() );
      }
      h->SetStats(0);
      h->SetMarkerStyle(22);
      h->SetMarkerColor(4);
      h->SetMarkerSize(1.6);
      h->Draw("psame");
      leg->AddEntry( h, "exp.data", "p" );

//      
//      TGraph* gr1 = new TGraph( NDModes, ModeID, KaonicHyBR );
//      gr1->SetLineColor(4);
//      gr1->SetMarkerStyle(22);
//      gr1->SetMarkerSize(1.6);
//      gr1->Draw("p");
//      leg->AddEntry( gr1, "exp.data", "p" ); 
//
   }
   
      
   leg->Draw();
   leg->SetFillColor(kWhite);

   return ;

}

void setStyle() 
{

  gStyle->SetCanvasBorderMode(0); gStyle->SetCanvasColor(kWhite);
  gStyle->SetPadColor(kWhite);    gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);   gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);   gStyle->SetFrameLineWidth(1);
  gStyle->SetTitleOffset(1.6,"Y");  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(1);
  
  return;

}

