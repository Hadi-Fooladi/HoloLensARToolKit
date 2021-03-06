/*
 *  mDet.c
 *  ARToolKit5
 *
 *  This file is part of ARToolKit.
 *
 *  ARToolKit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ARToolKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with ARToolKit.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  As a special exception, the copyright holders of this library give you
 *  permission to link this library with independent modules to produce an
 *  executable, regardless of the license terms of these independent modules, and to
 *  copy and distribute the resulting executable under terms of your choice,
 *  provided that you also meet, for each linked independent module, the terms and
 *  conditions of the license of that module. An independent module is a module
 *  which is neither derived from nor based on this library. If you modify this
 *  library, you may extend this exception to your version of the library, but you
 *  are not obligated to do so. If you do not wish to do so, delete this exception
 *  statement from your version.
 *
 *  Copyright 2015 Daqri, LLC.
 *  Copyright 2002-2015 ARToolworks, Inc.
 *
 *  Author(s): Shinsaku Hiura, Hirokazu Kato
 *
 */
/*******************************************************
 *
 * Author: Shinsaku Hiura, Hirokazu Kato
 *
 *         shinsaku@sys.es.osaka-u.ac.jp
 *         kato@sys.im.hiroshima-cu.ac.jp
 *
 * Revision: 2.1
 * Date: 99/07/16
 *
 *******************************************************/

#include <stdio.h>
#include <math.h>
#include <AR/ar.h>

#define MATRIX(name,x,y,width)  ( *(name + (width) * (x) + (y)) )

static ARdouble mdet( ARdouble *ap, int dimen, int rowa );

ARdouble arMatrixDet(ARMat *m)
{

	if(m->row != m->clm) return 0.0;

	return mdet(m->m, m->row, m->row);
}



static ARdouble mdet(ARdouble *ap, int dimen, int rowa)
/*  ARdouble  *ap;          input matrix */
/*  int     dimen;        Dimension of linre and row, those must be equal,
                          that is square matrix.       */
/*  int     rowa;         ROW Dimension of matrix A    */
{
    ARdouble det = 1.0;
    ARdouble work;
    int    is = 0;
    int    mmax;
    int    i, j, k;

    for(k = 0; k < dimen - 1; k++) {
        mmax = k;
        for(i = k + 1; i < dimen; i++)
            if (fabs(MATRIX(ap, i, k, rowa)) > fabs(MATRIX(ap, mmax, k, rowa)))
                mmax = i;
        if(mmax != k) {
            for (j = k; j < dimen; j++) {
                work = MATRIX(ap, k, j, rowa);
                MATRIX(ap, k, j, rowa) = MATRIX(ap, mmax, j, rowa);
                MATRIX(ap, mmax, j, rowa) = work;
            }
            is++;
        }
        for(i = k + 1; i < dimen; i++) {
            work = MATRIX(ap, i, k, rowa) / MATRIX(ap, k, k, rowa);
            for (j = k + 1; j < dimen; j++)
                MATRIX(ap, i, j, rowa) -= work * MATRIX(ap, k, j, rowa);
        }
    }
    for(i = 0; i < dimen; i++)
        det *= MATRIX(ap, i, i, rowa);
    for(i = 0; i < is; i++) 
        det *= -1.0;
    return(det);
}
