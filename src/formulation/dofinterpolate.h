// sparselizard - Copyright (C) 2017- A. Halbach
//
// See the LICENSE file for license information. Please report all
// bugs and problems to <alexandre.halbach at gmail.com>.

#ifndef DOFINTERPOLATE_H
#define DOFINTERPOLATE_H

#include "universe.h"
#include <vector>
#include "disjointregions.h"
#include "densematrix.h"
#include "intdensematrix.h"
#include "dofmanager.h"
#include "field.h"
#include "rawfield.h"
#include "expression.h"
#include "disjointregionselector.h"
#include "elementselector.h"
#include "hierarchicalformfunction.h"
#include "polynomial.h"
#include "polynomials.h"
#include <memory>

//// TO CHECK:
//
////////// MAKE SURE A DOF AND ON DOF CANNOT BE MERGED IN THE SAME TERM!!!!!!!!!!!!!

class dofinterpolate
{
    private:
    
        bool errorifnotfound = true;
        
        // The dof field:
        std::shared_ptr<rawfield> mydoffield = NULL;
        // Dof operations on the above doffield. Same doffield for all operations!
        std::vector<std::shared_ptr<operation>> mydofops = {};
        
        // Dof manager of the calling formulation:
        std::shared_ptr<dofmanager> mydofmanager = NULL;
        
        // All disjoint regions on the dof side (can have different element types and dof orders).
        std::vector<int> ondisjregs = {};
        
        // Reference evaluation coordinates.
        std::vector<double> myrefcoords = {};
        int mynumrefcoords = -1;
        
        // Dof interpolation x, y, z coordinates:
        std::vector<double> myxyzcoords = {};
        
        // Keep track of which coordinate was found.
        std::vector<bool> isfound = {};
        
        referencecoordinategroup rcg;
        

        // Max number of shape functions over all disjoint regions.
        int mymaxnumff = 0;
        
        // One matrix per dof field.
        // Rows are the elements in the calling region. 
        // Number of columns is maxnumff*numevalpoints (blocks of numevalpoints side by side).
        std::vector<densematrix> myvals = {};
        
        // One matrix per dof harmonic. Harmonic h is at mydofnums[h][0].
        // Value is -2 for non existing entries.
        std::vector<std::vector<intdensematrix>> mydofnums = {};
        
        
        // Create the matrix containers:
        void eval(void);
        
    public:
        
        dofinterpolate(void) {};

        dofinterpolate(std::vector<double> refcoords, elementselector& elemselec, std::vector<std::shared_ptr<operation>> dofops, std::shared_ptr<dofmanager> dofmngr, std::vector<int> othersidedisjreg);
        
        densematrix getvalues(elementselector& elemselec, int dofindex);
        intdensematrix getadresses(elementselector& elemselec, int harmnum);
                                            
};

#endif
