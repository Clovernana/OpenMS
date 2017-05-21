// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Timo Sachsenberg $
// $Authors: $
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/ClassTest.h>
#include <OpenMS/test_config.h>

#include <OpenMS/TRANSFORMATIONS/FEATUREFINDER/FeatureFinderAlgorithmIsotopeWavelet.h>

START_TEST(FeatureFinderAlgorithmIsotopeWavelet, "$Id$")

using namespace OpenMS;
using namespace std;

typedef FeatureFinderAlgorithmIsotopeWavelet FFASS;

FFASS* ptr = 0;
FFASS* nullPointer = 0;
FeatureFinderAlgorithm* ffA_nullPointer = 0;

START_SECTION((FeatureFinderAlgorithmIsotopeWavelet()))
	ptr = new FFASS;
  TEST_NOT_EQUAL(ptr,nullPointer)
END_SECTION

START_SECTION(IsotopeWaveletTransform<PeakType>::TransSpectrum* prepareHRDataCuda(const UInt i, IsotopeWaveletTransform< PeakType > *iwt))
	NOT_TESTABLE
END_SECTION

START_SECTION(MSSpectrum<PeakType>* createHRData(const UInt i))
	NOT_TESTABLE
END_SECTION

START_SECTION(virtual ~FeatureFinderAlgorithmIsotopeWavelet())
	delete ptr;
END_SECTION

START_SECTION(void run())
	NOT_TESTABLE
END_SECTION

START_SECTION((static FeatureFinderAlgorithm<PeakType>* create()))
  FeatureFinderAlgorithm* ptr2 = FFASS::create();
  TEST_NOT_EQUAL(ptr2,ffA_nullPointer)
	delete ptr2;
END_SECTION

START_SECTION(static const String getProductName())
	TEST_EQUAL(FFASS::getProductName(),"isotope_wavelet")
END_SECTION

END_TEST
