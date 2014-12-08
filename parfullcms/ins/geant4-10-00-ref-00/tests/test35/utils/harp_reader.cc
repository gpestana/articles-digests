//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//
//      File name:     Test30
//
//      Author:        V.Ivanchenko 
// 
//      Creation date: 19 February 2006
//
//      Modifications: 
//
// -------------------------------------------------------------------

#include "globals.hh"
#include "G4DataVector.hh"
#include "G4ios.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main(int argc, char** argv)
{
  int verbose = 1;

  // -------------------------------------------------------------------
  // Control on input

  if(argc < 2) {
    G4cout << "Input file is not specified! Exit" << G4endl;
    exit(1);
  }

  std::ifstream* fin = new std::ifstream();
  const std::string fname = argv[1];
  fin->open(fname.c_str());
  if( !fin->is_open()) {
    G4cout << "Input file <" << fname << "> does not exist! Exit" << G4endl;
    exit(1);
  }

  std::ofstream* fout_a = new std::ofstream();
  std::string fname1 = "dsde.dat";
  fout_a->open(fname1.c_str(), std::ios::out|std::ios::trunc);
  std::ofstream* fout_b = new std::ofstream();
  std::string fname2 = "dsdtet.dat";
  fout_b->open(fname2.c_str());//, std::ios::out|std::ios::trunc);
  std::ofstream* fout_c = new std::ofstream();
  std::string fname3 = "dsdedtet.dat";
  fout_c->open(fname3.c_str(), std::ios::out|std::ios::trunc);

  //there can't be lines longer than nmax characters
  const int nmax = 200;
  char line[nmax]; 
  std::string line1, line2, word1, word2, word3;
  G4bool end = true;

  G4DataVector* energy = new G4DataVector();
  int nbin = 100;
  int ibin, inum;
  int counter = 0;
  double bin0 = 2.0*MeV;
  double bin = 10.0*MeV;
  double elim= 30.0*MeV;
  double x, an, e1, e2, y1, y2, ct1, ct2, xs, de;
  double e0 = 0.0;

  x = 0.0;

  for(int i=0; i<=nbin; i++) {
    if(x < elim) {
      x += bin0;
      if(std::fabs(x - elim) < 0.01) x = elim;
    } else {
      x += bin;
    }
    energy->push_back(x);
  }

  G4DataVector* angle = new G4DataVector();
  std::vector<G4DataVector*> cs;

  // main loop 

  do {

    // read next line

    counter++;
    for(int ii = 0; ii < nmax; ii++) {line[ii] = ' ';}
    fin->getline( line, nmax);
    line1 = std::string("");
    line1 = std::string(line, nmax);
    if(1 < verbose) {
      std::cout << "Next line # " << counter << ": " << line1 << std::endl;
      std::cout << "First symbols= " 
		<< line[0] << line[1] << line[2] << std::endl;
    }  

    // analize line contence

    // end of file
    if(fin->eof()) {
      end = false;
    } else if(line[0] == 'A' && line[1] == 'D' && line[2] == 'E') {

      G4bool enddata = true;
      G4DataVector* cross = 0;
      ibin= 0;
      inum= 0;

      do {
        (*fin) >> an >> e1 >> e2 >> x >> xs;
        an *= degree;      
        if(1 < verbose) {
          std::cout << "an= " << an/degree << " e1= " << e1 
		    << " e2= " << e2 << " cross= " << x
		    << " +- " << xs << " %" 
		    << std::endl;
        }  

        if (e1 == 0.0) {
          enddata = false;
          end = false;
    	  }

        if((xs == 0.0 && an/degree > 10.) || !enddata) {

          // fill the rest by zero cross section
          for(int jj=ibin; jj<nbin; jj++) {
            cross->push_back(0.0);
          }

          cs.push_back(cross);
          if(0 < verbose) {
            std::cout << "Save data vector for  "
                      << " Angle(degree)= " 
		      << (*angle)[angle->size()-1]/degree
                      << G4endl;
            (*fout_c) << "#####..Result.of.parcing..####### "
                      << " Angle(degree)= " 
		      << (*angle)[angle->size()-1]/degree
                      << G4endl;
            for(int ii=0; ii<nbin; ii++) {
               (*fout_c) << "e(MeV)= " 
			 << 0.5*((*energy)[ii] + (*energy)[ii+1]) 
                         << " cross(mb/MeV/sr)= " << (*cross)[ii] 
			 << std::endl;
	    }
          }  
	}

	// new data
        if(xs == 0.0) {
          angle->push_back(an);
          cross = new G4DataVector();
          cross->push_back(0.0);
          ibin= 0;
          inum= 0;

        } else if(end) {

	  int j;
	  for(j=ibin; j<nbin; j++) {
            e0 = (*energy)[j];
            de = bin;
            if (e0 < elim) de = bin0;
            if (e1 >= e0 && e2 <= e0 + de) break;
            if(inum) (*cross)[j] /= (double)inum;
            inum = 0;
            cross->push_back(0.0);
	  }
          (*cross)[j] += x;
          inum++;
          ibin = j;
        }      

      } while (enddata);
     
      angle->push_back(pi);
      int na = angle->size();
      G4DataVector* f1;
      G4DataVector* f2;
  
      if(0 < verbose) {
        (*fout_a) << "#####..Result.of.integration..#####.."
                  << G4endl;
        (*fout_b) << "#####..Result.of.integration..#####.. Elim(MeV)= " 
                  << elim/MeV
                  << G4endl;
        for(int i=0; i<nbin; i++) {
        
          x = 0.0;
          for(int j=0; j<na-1; j++) {
            f1  = cs[j];  
            y1  = (*f1)[i];  
            ct1 = std::cos((*angle)[j]);
            if(j == 0) {
              f2  = cs[j+1]; 
              y2  = (*f2)[i]; 
              ct2 = std::cos((*angle)[j+1]);
              y1 += (y2 - y1)*(1.0 - ct1)/(ct2 - ct1);
              ct1 = 1.0;
              if(y1 < 0.0) y1 = 0.0;
	    } else if (j == na-2) {
              f2  = cs[j-1]; 
              y2  = (*f2)[i]; 
              ct2 = std::cos((*angle)[j-1]);
              y2 -= (y2 - y1)*(ct2 + 1.0)/(ct2 - ct1);
              ct2 = -1.0;
              if(y2 < 0.0) y2 = 0.0;
            } else {
              f2  = cs[j+1]; 
              y2  = (*f2)[i]; 
              ct2 = std::cos((*angle)[j+1]);
	    }
	    //	    cout << "f1= " << f1 << " f2= " << f2 << endl;
	    //cout << "y1= " << y1 << " y2= " << y2 << endl;
	    //cout << "ct1= " << ct1 << " ct2= " << ct2 << endl;
            x  += 0.5*(y1 + y2)*(ct1 - ct2);  
          }        
          x *= twopi;
          if(verbose > 1) {
            std::cout << "e(MeV)= " << 0.5*((*energy)[i] + (*energy)[i+1]) 
		      << " cross(mb/MeV)= " << x << std::endl;
	  }
          (*fout_a) << "e(MeV)= " << 0.5*((*energy)[i] + (*energy)[i+1]) 
                    << " cross(mb/MeV)= " << x << std::endl;
        }

        for(int j=0; j<na-1; j++) {
          f1  = cs[j];  
          an  = std::cos((*angle)[j]);
          x   = 0.0;
          for(int i=0; i<nbin; i++) {
            y1  = (*f1)[i];
            e1  = (*energy)[i];
            e2  = (*energy)[i+1];
            if(e2 < elim) {
              y1 = 0.0;
            } else if (e1 < elim) {
              y1 *= (e2 - elim)/(e2 - e1);
	    }
            x += y1*(e2 - e1);
          }
          (*fout_b) << "cos(theta)= " << an 
                    << " cross(mb/sr)= " << x << std::endl;
        }
      }
    }
  } while (end);
  (*fout_a) << "#####..End..#####" << std::endl;
  (*fout_b) << "#####..End..#####" << std::endl;
  (*fout_c) << "#####..End..#####" << std::endl;
}








