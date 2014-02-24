// -*- C++ -*-
//
// Package:    RecHitAnalyzer
// Class:      RecHitAnalyzer
// 
/**\class RecHitAnalyzer RecHitAnalyzer.cc GEMCode/RecHitAnalyzer/plugins/RecHitAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Claudio Caputo
//         Created:  Thu, 06 Feb 2014 13:57:03 GMT
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/ESHandle.h>
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "RecoMuon/TrackingTools/interface/MuonPatternRecoDumper.h"

#include "SimDataFormats/Track/interface/SimTrackContainer.h"

#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include <Geometry/GEMGeometry/interface/GEMEtaPartition.h>
#include "Geometry/GEMGeometry/interface/GEMEtaPartitionSpecs.h"
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>

#include "DataFormats/Provenance/interface/Timestamp.h"

#include <DataFormats/MuonDetId/interface/GEMDetId.h>

#include "RecoMuon/DetLayers/interface/MuonDetLayerGeometry.h"
#include "RecoMuon/Records/interface/MuonRecoGeometryRecord.h"

#include "RecoMuon/DetLayers/interface/MuRodBarrelLayer.h"
#include "RecoMuon/DetLayers/interface/MuDetRod.h"
#include "RecoMuon/DetLayers/interface/MuRingForwardDoubleLayer.h"
#include "RecoMuon/DetLayers/interface/MuDetRing.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"

#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"

//Structures used for filling ME
#include "GEMCode/RecHitAnalyzer/src/SimRecStructures.h"

using namespace std;
using namespace edm;



//
// class declaration
//

class RecHitAnalyzer : public edm::EDAnalyzer {
   public:
      explicit RecHitAnalyzer(const edm::ParameterSet&);
      ~RecHitAnalyzer();
    
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
//
//      MonitorElement * hNumGEMSimHits;
//      MonitorElement * hNumGEMRecHits;
//      MonitorElement * hSimHitOccupancy;
    
   private:
   // void bookMonitorElement(std::map<std::string, MonitorElement*> map_ME);
    bool isGEMRecHitMatched(MyGEMRecHit gem_recHit_, MyGEMSimHit gem_sh);
    void buildLUT();
    std::pair<int,int> getClosestChambers(int region, float phi);
     virtual void beginJob() override;
     virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
     virtual void endJob() override;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
    
    bool debug_;
    std::string folderPath_;
    bool EffSaveRootFile_;
    std::string EffRootFileName_;
    
    DQMStore * dbe;
    
    //std::map<int, std::map<std::string, MonitorElement*> >  meCollection;
    typedef std::map<std::string, MonitorElement*>  MEmap;
    MEmap meCollection;
    //std::map<int, MEmap>;
    
    edm::Handle<GEMRecHitCollection> gemRecHits_;
    edm::Handle<edm::PSimHitContainer> GEMHits;
    edm::Handle<edm::SimTrackContainer> sim_tracks;
    edm::Handle<edm::SimVertexContainer> sim_vertices;
    edm::ESHandle<GEMGeometry> gem_geom_;
    
    const GEMGeometry* gem_geometry_;
    
    /*-------------------------------------------------*/
    //This structures are defined in "SimRecStructures.h"
    MyGEMRecHit gem_recHit_;
    MyGEMSimHit gem_sh;
    MySimTrack track_;
    /*-------------------------------------------------*/
    
    //edm::ParameterSet cfg_;
    
    edm::InputTag simTrackInput_;
    edm::InputTag gemSimHitInput_;
    edm::InputTag gemRecHitInput_;
    
    double simTrackMinPt_;
    double simTrackMaxPt_;
    double simTrackMinEta_;
    double simTrackMaxEta_;
    double simTrackOnlyMuon_;
    float radiusCenter_;
    float chamberHeight_;
    
    std::pair<std::vector<float>,std::vector<int> > positiveLUT_;
    std::pair<std::vector<float>,std::vector<int> > negativeLUT_;
    
    bool hasGEMGeometry_=true;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RecHitAnalyzer::RecHitAnalyzer(const edm::ParameterSet& iConfig):
debug_(iConfig.getUntrackedParameter<bool>("debug")),
folderPath_(iConfig.getUntrackedParameter<std::string>("folderPath")),
EffSaveRootFile_(iConfig.getUntrackedParameter<bool>("EffSaveRootFile")),
EffRootFileName_(iConfig.getUntrackedParameter<std::string>("EffRootFileName"))
{
    dbe = edm::Service<DQMStore>().operator->();
    
    if(debug_) std::cout<<"booking Global histograms with "<<folderPath_<<std::endl;
    
    std::string folder;
    folder = folderPath_;
    dbe->setCurrentFolder(folder);
    
    //bookMonitorElement(meCollection);
    //---------------------ClustersSize--------------------------------------//
    meCollection["clsDistribution"] = dbe->book1D("clsDistribution","ClusterSizeDistribution",11,-0.5,10.5);
    meCollection["clsDistribution_rm1_l1"] = dbe->book1D("clsDistribution_rm1_l1","ClusterSizeDistribution, Region=-1, Layer=1",11,-0.5,10.5);
    meCollection["clsDistribution_rm1_l2"] = dbe->book1D("clsDistribution_rm1_l2","ClusterSizeDistribution, Region=-1, Layer=2",11,-0.5,10.5);
    meCollection["clsDistribution_rp1_l1"] = dbe->book1D("clsDistribution_rp1_l1","ClusterSizeDistribution, Region=1, Layer=1",11,-0.5,10.5);
    meCollection["clsDistribution_rp1_l2"] = dbe->book1D("clsDistribution_rp1_l2","ClusterSizeDistribution, Region=1, Layer=2",11,-0.5,10.5);
    //-----------------------BunchX--------------------------------------//
    meCollection["bxDistribution"] = dbe->book1D("bxDistribution","BunchCrossingDistribution",11,-5.5,5.5);
    meCollection["bxDistribution_st1"] = dbe->book1D("bxDistribution_st1","BunchCrossingDistribution, Station=1",11,-5.5,5.5);
    meCollection["bxDistribution_st2"] = dbe->book1D("bxDistribution_st2","BunchCrossingDistribution, Station=2",11,-5.5,5.5);
    meCollection["bxDistribution_st3"] = dbe->book1D("bxDistribution_st3","BunchCrossingDistribution, Station=3",11,-5.5,5.5);
    //-------------------------(x_rec-x_sim)/x_sim-----------------------------------//
    meCollection["recHitPullX"] = dbe->book1D("recHitPullX","recHitPullX",100,-50,+50);
    
    meCollection["recHitPullX_rm1_st1_l1"] = dbe->book1D("recHitPullX_rm1_st1_l1","recHitPullX, region-1, station1, layer1",100,-50,+50);
    meCollection["recHitPullX_rm1_st1_l2"] = dbe->book1D("recHitPullX_rm1_st1_l2","recHitPullX, region-1, station1, layer2",100,-50,+50);
    meCollection["recHitPullX_rp1_st1_l1"] = dbe->book1D("recHitPullX_rp1_st1_l1","recHitPullX, region1, station1, layer1",100,-50,+50);
    meCollection["recHitPullX_rp1_st1_l2"] = dbe->book1D("recHitPullX_rp1_st1_l2","recHitPullX, region1, station1, layer2",100,-50,+50);
    
    meCollection["recHitPullX_rm1_st2_l1"] = dbe->book1D("recHitPullX_rm1_st2_l1","recHitPullX, region-1, station1, layer1",100,-50,+50);
    meCollection["recHitPullX_rm1_st2_l2"] = dbe->book1D("recHitPullX_rm1_st2_l2","recHitPullX, region-1, station1, layer2",100,-50,+50);
    meCollection["recHitPullX_rp1_st2_l1"] = dbe->book1D("recHitPullX_rp1_st2_l1","recHitPullX, region1, station1, layer1",100,-50,+50);
    meCollection["recHitPullX_rp1_st2_l2"] = dbe->book1D("recHitPullX_rp1_st2_l2","recHitPullX, region1, station1, layer2",100,-50,+50);
    
    meCollection["recHitPullX_rm1_st3_l1"] = dbe->book1D("recHitPullX_rm1_st3_l1","recHitPullX, region-1, station3, layer1",100,-50,+50);
    meCollection["recHitPullX_rm1_st3_l2"] = dbe->book1D("recHitPullX_rm1_st3_l2","recHitPullX, region-1, station3, layer2",100,-50,+50);
    meCollection["recHitPullX_rp1_st3_l1"] = dbe->book1D("recHitPullX_rp1_st3_l1","recHitPullX, region1, station3, layer1",100,-50,+50);
    meCollection["recHitPullX_rp1_st3_l2"] = dbe->book1D("recHitPullX_rp1_st3_l2","recHitPullX, region1, station3, layer2",100,-50,+50);
    
    
    //-----------------------------------------------------------//
    meCollection["recHitDPhi"] = dbe->book1D("recHitDPhi","DeltaPhi RecHit",100,-0.001,+0.001);
    meCollection["recHitDPhi_st1"] = dbe->book1D("recHitDPhi_st1","DeltaPhi RecHit, Station=1",100,-0.001,+0.001);
    meCollection["recHitDPhi_st2"] = dbe->book1D("recHitDPhi_st2","DeltaPhi RecHit, Station=2",100,-0.001,+0.001);
    meCollection["recHitDPhi_st3"] = dbe->book1D("recHitDPhi_st3","DeltaPhi RecHit, Station=3",100,-0.001,+0.001);
    
//    meCollection["recHitDPhi_rm1_l1"] = dbe->book1D("recHitDPhi_rm1_l1","DeltaPhi RecHit, Region=-1, Layer=1",100,-0.001,+0.001);
//    meCollection["recHitDPhi_rm1_l2"] = dbe->book1D("recHitDPhi_rm1_l2","DeltaPhi RecHit, Region=-1, Layer=2",100,-0.001,+0.001);
//    meCollection["recHitDPhi_rp1_l1"] = dbe->book1D("recHitDPhi_rp1_l1","DeltaPhi RecHit, Region=1, Layer=1",100,-0.001,+0.001);
//    meCollection["recHitDPhi_rp1_l2"] = dbe->book1D("recHitDPhi_rp1_l2","DeltaPhi RecHit, Region=1, Layer=2",100,-0.001,+0.001);
    
    meCollection["recHitDPhi_st1_cls1"] = dbe->book1D("recHitDPhi_st1_cls1","DeltaPhi RecHit, Station=1, CLS=1",100,-0.001,+0.001);
    meCollection["recHitDPhi_st1_cls2"] = dbe->book1D("recHitDPhi_st1_cls2","DeltaPhi RecHit, Station=1, CLS=2",100,-0.001,+0.001);
    meCollection["recHitDPhi_st1_cls3"] = dbe->book1D("recHitDPhi_st1_cls3","DeltaPhi RecHit, Station=1, CLS=3",100,-0.001,+0.001);
    
    meCollection["recHitDPhi_st2_cls1"] = dbe->book1D("recHitDPhi_st2_cls1","DeltaPhi RecHit, Station=2, CLS=1",100,-0.001,+0.001);
    meCollection["recHitDPhi_st2_cls2"] = dbe->book1D("recHitDPhi_st2_cls2","DeltaPhi RecHit, Station=2, CLS=2",100,-0.001,+0.001);
    meCollection["recHitDPhi_st2_cls3"] = dbe->book1D("recHitDPhi_st2_cls3","DeltaPhi RecHit, Station=2, CLS=3",100,-0.001,+0.001);
    
    meCollection["recHitDPhi_st3_cls1"] = dbe->book1D("recHitDPhi_st3_cls1","DeltaPhi RecHit, Station=3, CLS=1",100,-0.001,+0.001);
    meCollection["recHitDPhi_st3_cls2"] = dbe->book1D("recHitDPhi_st3_cls2","DeltaPhi RecHit, Station=3, CLS=2",100,-0.001,+0.001);
    meCollection["recHitDPhi_st3_cls3"] = dbe->book1D("recHitDPhi_st3_cls3","DeltaPhi RecHit, Station=3, CLS=3",100,-0.001,+0.001);
    //-------------------------------------------------//
    meCollection["localrh_xy_rm1_st1_l1"] = dbe->book2D("localrh_xy_rm1_st1_l1","GEM RecHit occupancy: region-1, station1, layer1",200,-260,260,100,-260,260);
    meCollection["localrh_xy_rm1_st1_l2"] = dbe->book2D("localrh_xy_rm1_st1_l2","GEM RecHit occupancy: region-1, station1, layer2",200,-260,260,100,-260,260);
    meCollection["localrh_xy_rp1_st1_l1"] = dbe->book2D("localrh_xy_rp1_st1_l1","GEM RecHit occupancy: region1, station1, layer1",200,-260,260,100,-260,260);
    meCollection["localrh_xy_rp1_st1_l2"] = dbe->book2D("localrh_xy_rp1_st1_l2","GEM RecHit occupancy: region1, station1, layer2",200,-260,260,100,-260,260);
    
    meCollection["localrh_xy_rm1_st2_l1"] = dbe->book2D("localrh_xy_rm1_st2_l1","GEM RecHit occupancy: region-1, station2, layer1",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rm1_st2_l2"] = dbe->book2D("localrh_xy_rm1_st2_l2","GEM RecHit occupancy: region-1, station2, layer2",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rp1_st2_l1"] = dbe->book2D("localrh_xy_rp1_st2_l1","GEM RecHit occupancy: region1, station2, layer1",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rp1_st2_l2"] = dbe->book2D("localrh_xy_rp1_st2_l2","GEM RecHit occupancy: region1, station2, layer2",200,-360,360,200,-360,360);
    
    meCollection["localrh_xy_rm1_st3_l1"] = dbe->book2D("localrh_xy_rm1_st3_l1","GEM RecHit occupancy: region-1, station3, layer1",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rm1_st3_l2"] = dbe->book2D("localrh_xy_rm1_st3_l2","GEM RecHit occupancy: region-1, station3, layer2",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rp1_st3_l1"] = dbe->book2D("localrh_xy_rp1_st3_l1","GEM RecHit occupancy: region1, station3, layer1",200,-360,360,200,-360,360);
    meCollection["localrh_xy_rp1_st3_l2"] = dbe->book2D("localrh_xy_rp1_st3_l2","GEM RecHit occupancy: region1, station3, layer2",200,-360,360,200,-360,360);
    
    meCollection["localrh_zr_rm1_st1"] = dbe->book2D("localrh_zr_rm1_st1","GEM RecHit occupancy: region-1",200,-573,-564,110,130,240);
    meCollection["localrh_zr_rp1_st1"] = dbe->book2D("localrh_zr_rp1_st1","GEM RecHit occupancy: region1",200,573,564,110,130,240);
    //-------------------------------------------------//
    //Maybe StripVsGlobalPhi
    
    //-------------------------------------------------//
    meCollection["strip_rh_tot"] = dbe->book1D("strip_rh_tot","GEM RecHit occupancy per strip number",384,0.5,384.5);
    
    meCollection["strip_rh_rm1_st1_l1_tot"] = dbe->book1D("strip_rh_rm1_st1_l1_tot","GEM RecHit occupancy per strip number, region-1 layer1 station1",384,0.5,384.5);
    meCollection["strip_rh_rm1_st1_l2_tot"] = dbe->book1D("strip_rh_rm1_st1_l2_tot","GEM RecHit occupancy per strip number, region-1 layer2 station1",384,0.5,384.5);
    meCollection["strip_rh_rp1_st1_l1_tot"] = dbe->book1D("strip_rh_rp1_st1_l1_tot","GEM RecHit occupancy per strip number, region1 layer1 station1",384,0.5,384.5);
    meCollection["strip_rh_rp1_st1_l2_tot"] = dbe->book1D("strip_rh_rp1_st1_l2_tot","GEM RecHit occupancy per strip number, region1 layer2 station1",384,0.5,384.5);
    
    meCollection["strip_rh_rm1_st2_l1_tot"] = dbe->book1D("strip_rh_rm1_st2_l1_tot","GEM RecHit occupancy per strip number, region-1 layer1 station2",768,0.5,768.5);
    meCollection["strip_rh_rm1_st2_l2_tot"] = dbe->book1D("strip_rh_rm1_st2_l2_tot","GEM RecHit occupancy per strip number, region-1 layer2 station2",768,0.5,768.5);
    meCollection["strip_rh_rp1_st2_l1_tot"] = dbe->book1D("strip_rh_rp1_st2_l1_tot","GEM RecHit occupancy per strip number, region1 layer1 station2",768,0.5,768.5);
    meCollection["strip_rh_rp1_st2_l2_tot"] = dbe->book1D("strip_rh_rp1_st2_l2_tot","GEM RecHit occupancy per strip number, region1 layer2 station2",768,0.5,768.5);
    
    meCollection["strip_rh_rm1_st3_l1_tot"] = dbe->book1D("strip_rh_rm1_st3_l1_tot","GEM RecHit occupancy per strip number, region-1 layer1 station3",768,0.5,768.5);
    meCollection["strip_rh_rm1_st3_l2_tot"] = dbe->book1D("strip_rh_rm1_st3_l2_tot","GEM RecHit occupancy per strip number, region-1 layer2 station3",768,0.5,768.5);
    meCollection["strip_rh_rp1_st3_l1_tot"] = dbe->book1D("strip_rh_rp1_st3_l1_tot","GEM RecHit occupancy per strip number, region1 layer1 station3",768,0.5,768.5);
    meCollection["strip_rh_rp1_st3_l2_tot"] = dbe->book1D("strip_rh_rp1_st3_l2_tot","GEM RecHit occupancy per strip number, region1 layer2 station3",768,0.5,768.5);
    
    
    //-------------------------------------------------//
    meCollection["roll_vs_strip_rh"] = dbe->book2D("roll_vs_strip_rh","GEM RecHit occupancy per roll and strip number",768,0.5,768.5,12,0.5,12.5);
    
    meCollection["roll_vs_strip_rh_rm1_st1_l1"] = dbe->book2D("roll_vs_strip_rh_rm1_st1_l1","GEM RecHit occupancy per roll and strip number, region-1 layer1 station1",384,0.5,384.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rm1_st1_l2"] = dbe->book2D("roll_vs_strip_rh_rm1_st1_l2","GEM RecHit occupancy per roll and strip number, region-1 layer2 station1",384,0.5,384.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st1_l1"] = dbe->book2D("roll_vs_strip_rh_rp1_st1_l1","GEM RecHit occupancy per roll and strip number, region1 layer1 station1",384,0.5,384.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st1_l2"] = dbe->book2D("roll_vs_strip_rh_rp1_st1_l2","GEM RecHit occupancy per roll and strip number, region1 layer2 station1",384,0.5,384.5,12,0.5,12.5);
    
    meCollection["roll_vs_strip_rh_rm1_st2_l1"] = dbe->book2D("roll_vs_strip_rh_rm1_st2_l1","GEM RecHit occupancy per roll and strip number, region-1 layer1 station2",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rm1_st2_l2"] = dbe->book2D("roll_vs_strip_rh_rm1_st2_l2","GEM RecHit occupancy per roll and strip number, region-1 layer2 station2",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st2_l1"] = dbe->book2D("roll_vs_strip_rh_rp1_st2_l1","GEM RecHit occupancy per roll and strip number, region1 layer1 station2",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st2_l2"] = dbe->book2D("roll_vs_strip_rh_rp1_st2_l2","GEM RecHit occupancy per roll and strip number, region1 layer2 station2",768,0.5,768.5,12,0.5,12.5);
    
    meCollection["roll_vs_strip_rh_rm1_st3_l1"] = dbe->book2D("roll_vs_strip_rh_rm1_st3_l1","GEM RecHit occupancy per roll and strip number, region-1 layer1 station3",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rm1_st3_l2"] = dbe->book2D("roll_vs_strip_rh_rm1_st3_l2","GEM RecHit occupancy per roll and strip number, region-1 layer2 station3",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st3_l1"] = dbe->book2D("roll_vs_strip_rh_rp1_st3_l1","GEM RecHit occupancy per roll and strip number, region1 layer1 station3",768,0.5,768.5,12,0.5,12.5);
    meCollection["roll_vs_strip_rh_rp1_st3_l2"] = dbe->book2D("roll_vs_strip_rh_rp1_st3_l2","GEM RecHit occupancy per roll and strip number, region1 layer2 station3",768,0.5,768.5,12,0.5,12.5);
    
    //-------------------------------------------------//
    
}


RecHitAnalyzer::~RecHitAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//void RecHitAnalyzer::bookMonitorElement(std::map<std::string, MonitorElement*> map_ME){
//    
//    map_ME["hNumGEMSimHits"] = dbe->book1D("NumGEMSimHits","NumGEMSimHits",11,-0.5,10.5);
//    map_ME["hNumGEMRecHits"] = dbe->book1D("NumGEMRecHits","NumGEMRecHits",11,-0.5,10.5);
//
//}
//
// member functions
//
bool RecHitAnalyzer::isGEMRecHitMatched(MyGEMRecHit gem_recHit_, MyGEMSimHit gem_sh)
{
    
    Int_t gem_region = gem_recHit_.region;
    Int_t gem_layer = gem_recHit_.layer;
    Int_t gem_station = gem_recHit_.station;
    Int_t gem_chamber = gem_recHit_.chamber;
    Int_t gem_roll = gem_recHit_.roll;
    Int_t gem_firstStrip = gem_recHit_.firstClusterStrip;
    Int_t gem_cls = gem_recHit_.clusterSize;
    
    Int_t gem_sh_region = gem_sh.region;
    Int_t gem_sh_layer = gem_sh.layer;
    Int_t gem_sh_station = gem_sh.station;
    Int_t gem_sh_chamber = gem_sh.chamber;
    Int_t gem_sh_roll = gem_sh.roll;
    Int_t gem_sh_strip = gem_sh.strip;
    
    std::vector<int> stripsFired;
    for(int i = gem_firstStrip; i < (gem_firstStrip + gem_cls); i++){
        
        stripsFired.push_back(i);
        
    }
    
    bool cond1, cond2, cond3;
    
    if(gem_sh_region == gem_region && gem_sh_layer == gem_layer && gem_sh_station == gem_station) cond1 = true;
    else cond1 = false;
    if(gem_sh_chamber == gem_chamber && gem_sh_roll == gem_roll) cond2 = true;
    else cond2 = false;
    if(std::find(stripsFired.begin(), stripsFired.end(), (gem_sh_strip + 1)) != stripsFired.end()) cond3 = true;
    else cond3 = false;
    
    return (cond1 & cond2 & cond3);
    
}




// ------------ method called for each event  ------------
void
RecHitAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    //int num_simHit=0;
    
    iEvent.getByLabel(edm::InputTag("g4SimHits","MuonGEMHits"), GEMHits);
    iEvent.getByLabel(edm::InputTag("gemRecHits"), gemRecHits_);
    
    for (edm::PSimHitContainer::const_iterator itHit = GEMHits->begin(); itHit!=GEMHits->end(); ++itHit) {
        
        //const GEMDetId id(itHit->detUnitId());
        
        if(abs(itHit->particleType()) != 13) continue;
        //if(id.region()!=1) continue;
        //num_simHit++;
        gem_sh.eventNumber = iEvent.id().event();
        gem_sh.detUnitId = itHit->detUnitId();
        gem_sh.particleType = itHit->particleType();
        gem_sh.x = itHit->localPosition().x();
        gem_sh.y = itHit->localPosition().y();
        gem_sh.energyLoss = itHit->energyLoss();
        gem_sh.pabs = itHit->pabs();
        gem_sh.timeOfFlight = itHit->timeOfFlight();
        
        const GEMDetId id(itHit->detUnitId());
        
        gem_sh.region = id.region();
        gem_sh.ring = id.ring();
        gem_sh.station = id.station();
        gem_sh.layer = id.layer();
        gem_sh.chamber = id.chamber();
        gem_sh.roll = id.roll();
        
        const LocalPoint p0(0., 0., 0.);
        const GlobalPoint Gp0(gem_geometry_->idToDet(itHit->detUnitId())->surface().toGlobal(p0));
        
        gem_sh.Phi_0 = Gp0.phi();
        gem_sh.R_0 = Gp0.perp();
        gem_sh.DeltaPhi = atan(-1*id.region()*pow(-1,id.chamber())*itHit->localPosition().x()/(Gp0.perp() + itHit->localPosition().y()));
        
        const LocalPoint hitLP(itHit->localPosition());
        const GlobalPoint hitGP(gem_geometry_->idToDet(itHit->detUnitId())->surface().toGlobal(hitLP));
        gem_sh.globalR = hitGP.perp();
        gem_sh.globalEta = hitGP.eta();
        gem_sh.globalPhi = hitGP.phi();
        gem_sh.globalX = hitGP.x();
        gem_sh.globalY = hitGP.y();
        gem_sh.globalZ = hitGP.z();
        
        //  Now filling strip info using entry point rather than local position to be
        //  consistent with digi strips. To change back, just switch the comments - WHF
        //  gem_sh.strip=gem_geometry_->etaPartition(itHit->detUnitId())->strip(hitLP);
        const LocalPoint hitEP(itHit->entryPoint());
        gem_sh.strip = gem_geometry_->etaPartition(itHit->detUnitId())->strip(hitEP);
        
        int count = 0;
        //std::cout<<"SimHit: region "<<gem_sh.region<<" station "<<gem_sh.station<<" layer "<<gem_sh.layer<<" chamber "<<gem_sh.chamber<<" roll "<<gem_sh.roll<<" strip "<<gem_sh.strip<<" type "<<itHit->particleType()<<" id "<<itHit->trackId()<<std::endl;
        for (GEMRecHitCollection::const_iterator recHit = gemRecHits_->begin(); recHit != gemRecHits_->end(); ++recHit)
        {
            gem_recHit_.x = recHit->localPosition().x();
            gem_recHit_.xErr = recHit->localPositionError().xx();
            gem_recHit_.y = recHit->localPosition().y();
            gem_recHit_.detId = (Short_t) (*recHit).gemId();
            gem_recHit_.bx = recHit->BunchX();
            gem_recHit_.clusterSize = recHit->clusterSize();
            gem_recHit_.firstClusterStrip = recHit->firstClusterStrip();
            
            GEMDetId id((*recHit).gemId());
            
            gem_recHit_.region = (Short_t) id.region();
            gem_recHit_.ring = (Short_t) id.ring();
            gem_recHit_.station = (Short_t) id.station();
            gem_recHit_.layer = (Short_t) id.layer();
            gem_recHit_.chamber = (Short_t) id.chamber();
            gem_recHit_.roll = (Short_t) id.roll();
            
            LocalPoint hitLP = recHit->localPosition();
            GlobalPoint hitGP = gem_geometry_->idToDet((*recHit).gemId())->surface().toGlobal(hitLP);
            
            gem_recHit_.globalR = hitGP.perp();
            gem_recHit_.globalEta = hitGP.eta();
            gem_recHit_.globalPhi = hitGP.phi();
            gem_recHit_.globalX = hitGP.x();
            gem_recHit_.globalY = hitGP.y();
            gem_recHit_.globalZ = hitGP.z();
            
            gem_recHit_.x_sim = gem_sh.x;
            gem_recHit_.y_sim = gem_sh.y;
            gem_recHit_.globalEta_sim = gem_sh.globalEta;
            gem_recHit_.globalPhi_sim = gem_sh.globalPhi;
            gem_recHit_.globalX_sim = gem_sh.globalX;
            gem_recHit_.globalY_sim = gem_sh.globalY;
            gem_recHit_.globalZ_sim = gem_sh.globalZ;
            gem_recHit_.pull = (gem_sh.x - gem_recHit_.x) / gem_recHit_.xErr;
            
        /*-----------BunchCrossing----------------*/
            meCollection["bxDistribution"]->Fill(gem_recHit_.bx);
            if(gem_recHit_.station==1) meCollection["bxDistribution_st1"]->Fill(gem_recHit_.bx);
            if(gem_recHit_.station==2) meCollection["bxDistribution_st2"]->Fill(gem_recHit_.bx);
            if(gem_recHit_.station==3) meCollection["bxDistribution_st3"]->Fill(gem_recHit_.bx);
            
            if(gem_recHit_.bx != 0) continue;
            if(isGEMRecHitMatched(gem_recHit_, gem_sh))
            {
                bool verbose(false);
                if (verbose)
                    std::cout<<"RecHit: region "<<gem_recHit_.region<<" station "<<gem_recHit_.station
                    <<" layer "<<gem_recHit_.layer<<" chamber "<<gem_recHit_.chamber
                    <<" roll "<<gem_recHit_.roll<<" firstStrip "<<gem_recHit_.firstClusterStrip
                    <<" cls "<<gem_recHit_.clusterSize<<" bx "<<gem_recHit_.bx<<std::endl;
                
        /*----------------ClustersSize--------------------------*/
                meCollection["clsDistribution"]->Fill(gem_recHit_.clusterSize);
                if(gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["clsDistribution_rm1_l1"]->Fill(gem_recHit_.clusterSize);
                if(gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["clsDistribution_rm1_l2"]->Fill(gem_recHit_.clusterSize);
            
                if(gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["clsDistribution_rp1_l1"]->Fill(gem_recHit_.clusterSize);
                if(gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["clsDistribution_rp1_l2"]->Fill(gem_recHit_.clusterSize);
                
        /*-----------------------X pull--------------------------*/
                meCollection["recHitPullX"]->Fill(gem_recHit_.pull);
                
                //Station 1
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["recHitPullX_rm1_st1_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["recHitPullX_rm1_st1_l2"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["recHitPullX_rp1_st1_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["recHitPullX_rp1_st1_l2"]->Fill(gem_recHit_.pull);
                
                //Station 2
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["recHitPullX_rm1_st2_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["recHitPullX_rm1_st2_l2"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["recHitPullX_rp1_st2_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["recHitPullX_rp1_st2_l2"]->Fill(gem_recHit_.pull);
                
                //Station 3
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["recHitPullX_rm1_st2_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["recHitPullX_rm1_st2_l2"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["recHitPullX_rp1_st2_l1"]->Fill(gem_recHit_.pull);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["recHitPullX_rp1_st2_l2"]->Fill(gem_recHit_.pull);
                
        /*---------------------DeltaPhi-------------------------------*/
                double deltaPhi = gem_recHit_.globalPhi-gem_sh.globalPhi;
                
                meCollection["recHitDPhi"]->Fill(deltaPhi);
                if(gem_recHit_.station==1) meCollection["recHitDPhi_st1"]->Fill(deltaPhi);
                if(gem_recHit_.station==2) meCollection["recHitDPhi_st2"]->Fill(deltaPhi);
                if(gem_recHit_.station==3) meCollection["recHitDPhi_st3"]->Fill(deltaPhi);
                
                if(gem_recHit_.station==1 && gem_recHit_.clusterSize==1)meCollection["recHitDPhi_st1_cls1"]->Fill(deltaPhi);
                if(gem_recHit_.station==2 && gem_recHit_.clusterSize==1)meCollection["recHitDPhi_st2_cls1"]->Fill(deltaPhi);
                if(gem_recHit_.station==3 && gem_recHit_.clusterSize==1)meCollection["recHitDPhi_st3_cls1"]->Fill(deltaPhi);
                
                if(gem_recHit_.station==1 && gem_recHit_.clusterSize==2)meCollection["recHitDPhi_st1_cls2"]->Fill(deltaPhi);
                if(gem_recHit_.station==2 && gem_recHit_.clusterSize==2)meCollection["recHitDPhi_st2_cls2"]->Fill(deltaPhi);
                if(gem_recHit_.station==3 && gem_recHit_.clusterSize==2)meCollection["recHitDPhi_st3_cls2"]->Fill(deltaPhi);
                
                if(gem_recHit_.station==1 && gem_recHit_.clusterSize==3)meCollection["recHitDPhi_st1_cls3"]->Fill(deltaPhi);
                if(gem_recHit_.station==2 && gem_recHit_.clusterSize==3)meCollection["recHitDPhi_st2_cls3"]->Fill(deltaPhi);
                if(gem_recHit_.station==3 && gem_recHit_.clusterSize==3)meCollection["recHitDPhi_st3_cls3"]->Fill(deltaPhi);
                
        /*---------------------Occupancy XY---------------------------*/
                //Station 1
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["localrh_xy_rm1_st1_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["localrh_xy_rm1_st1_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["localrh_xy_rp1_st1_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["localrh_xy_rp1_st1_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                 
                
                //Station 2
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["localrh_xy_rm1_st2_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["localrh_xy_rm1_st2_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.region==1) meCollection["localrh_xy_rp1_st2_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["localrh_xy_rp1_st2_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                
                //Station 3
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["localrh_xy_rm1_st3_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["localrh_xy_rm1_st3_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.region==1) meCollection["localrh_xy_rp1_st3_l1"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["localrh_xy_rp1_st3_l2"]->Fill(gem_recHit_.globalX,gem_recHit_.globalY);

                
                double glb_R=sqrt(gem_recHit_.globalX*gem_recHit_.globalX+gem_recHit_.globalY*gem_recHit_.globalY);
                if(gem_recHit_.region==1) cout<<"Raggio Longitudinale: "<<glb_R<<" global Z : "<<gem_recHit_.globalZ<<endl;
                if(gem_recHit_.station==1 && gem_recHit_.region==-1) meCollection["localrh_zr_rm1_st1"]->Fill(gem_recHit_.globalZ,glb_R);
                if(gem_recHit_.station==1 && gem_recHit_.region==1) meCollection["localrh_zr_rp1_st1"]->Fill(gem_recHit_.globalZ,glb_R);
                
        /*-------------------Strips--------------------------------------*/
                
                meCollection["strip_rh_tot"]->Fill(gem_recHit_.firstClusterStrip);
                
                //Station 1
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["strip_rh_rm1_st1_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["strip_rh_rm1_st1_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["strip_rh_rp1_st1_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["strip_rh_rp1_st1_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                
                //Station 2
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["strip_rh_rm1_st2_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["strip_rh_rm1_st2_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["strip_rh_rp1_st2_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["strip_rh_rp1_st2_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                
                //Station 3
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["strip_rh_rm1_st3_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["strip_rh_rm1_st3_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["strip_rh_rp1_st3_l1_tot"]->Fill(gem_recHit_.firstClusterStrip);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["strip_rh_rp1_st3_l2_tot"]->Fill(gem_recHit_.firstClusterStrip);
                
        /*--------------------------StripsVsRolls------------------------*/
                meCollection["roll_vs_strip_rh"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                
                //Station 1
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rm1_st1_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==1 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rm1_st1_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rp1_st1_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==1 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rp1_st1_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                
                //Station 2
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rm1_st2_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==2 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rm1_st2_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rp1_st2_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==2 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rp1_st2_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                
                //Station 1
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rm1_st3_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==3 && gem_recHit_.region==-1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rm1_st3_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==1) meCollection["roll_vs_strip_rh_rp1_st3_l1"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                if(gem_recHit_.station==3 && gem_recHit_.region==1 && gem_recHit_.layer==2) meCollection["roll_vs_strip_rh_rp1_st3_l2"]->Fill(gem_recHit_.firstClusterStrip,gem_recHit_.roll);
                
                count++;
            }
        }
        gem_sh.countMatching = count;
        
    }
    std::cout<<"Info GEM Geomery:"<<gem_geometry_->stations().size()<<std::endl;
}
    
   // meCollection["hNumGEMSimHits"]->Fill(num_simHit);



// ------------ method called once each job just before starting event loop  ------------
void RecHitAnalyzer::beginJob(){
    
}

// ------------ method called once each job just after ending the event loop  ------------
void RecHitAnalyzer::endJob(){
    
    dbe = 0;
    
}

// ------------ method called when starting to processes a run  ------------

void 
RecHitAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    try {
        iSetup.get<MuonGeometryRecord>().get(gem_geom_);
        gem_geometry_ = &*gem_geom_;
    } catch (edm::eventsetup::NoProxyException<GEMGeometry>& e) {
        hasGEMGeometry_ = false;
        edm::LogWarning("GEMRecHitAnalyzer") << "+++ Info: GEM geometry is unavailable. +++\n";
    }
    
    if(hasGEMGeometry_) {
        
        // FIXME - when a geometry with different partition numbers will be released, the code will brake!
        const auto top_chamber = static_cast<const GEMEtaPartition*>(gem_geometry_->idToDetUnit(GEMDetId(1,1,1,1,1,1)));
        const int nEtaPartitions(gem_geometry_->chamber(GEMDetId(1,1,1,1,1,1))->nEtaPartitions());
        const auto bottom_chamber = static_cast<const GEMEtaPartition*>(gem_geometry_->idToDetUnit(GEMDetId(1,1,1,1,1,nEtaPartitions)));
        const float top_half_striplength = top_chamber->specs()->specificTopology().stripLength()/2.;
        const float bottom_half_striplength = bottom_chamber->specs()->specificTopology().stripLength()/2.;
        const LocalPoint lp_top(0., top_half_striplength, 0.);
        const LocalPoint lp_bottom(0., -bottom_half_striplength, 0.);
        const GlobalPoint gp_top = top_chamber->toGlobal(lp_top);
        const GlobalPoint gp_bottom = bottom_chamber->toGlobal(lp_bottom);
        
        radiusCenter_ = (gp_bottom.perp() + gp_top.perp())/2.;
        chamberHeight_ = gp_top.perp() - gp_bottom.perp();
        
        using namespace std;
        //cout<<"half top "<<top_half_striplength<<" bot "<<lp_bottom<<endl;
        //cout<<"r top "<<gp_top.perp()<<" bot "<<gp_bottom.perp()<<endl;
        LocalPoint p0(0.,0.,0.);
        //cout<<"r0 top "<<top_chamber->toGlobal(p0).perp()<<" bot "<< bottom_chamber->toGlobal(p0).perp()<<endl;
        //cout<<"rch "<<radiusCenter_<<" hch "<<chamberHeight_<<endl;
        
        buildLUT();
    }
}

void RecHitAnalyzer::buildLUT()
{
    std::vector<int> pos_ids;
    pos_ids.push_back(GEMDetId(1,1,1,1,36,1).rawId());
    
    std::vector<int> neg_ids;
    neg_ids.push_back(GEMDetId(-1,1,1,1,36,1).rawId());
    
    // VK: I would really suggest getting phis from GEMGeometry
    
    std::vector<float> phis;
    phis.push_back(0.);
    for(int i=1; i<37; ++i)
    {
        pos_ids.push_back(GEMDetId(1,1,1,1,i,1).rawId());
        neg_ids.push_back(GEMDetId(-1,1,1,1,i,1).rawId());
        phis.push_back(i*10.);
    }
    positiveLUT_ = std::make_pair(phis,pos_ids);
    negativeLUT_ = std::make_pair(phis,neg_ids);
}

std::pair<int,int> RecHitAnalyzer::getClosestChambers(int region, float phi)
{
    auto& phis(positiveLUT_.first);
    auto upper = std::upper_bound(phis.begin(), phis.end(), phi);
    //std::cout << "lower = " << upper - phis.begin() << std::endl;
    //std::cout << "upper = " << upper - phis.begin() + 1 << std::endl;
    auto& LUT = (region == 1 ? positiveLUT_.second : negativeLUT_.second);
    return std::make_pair(LUT.at(upper - phis.begin()), (LUT.at((upper - phis.begin() + 1)%36)));
}

// ------------ method called when ending the processing of a run  ------------

void 
RecHitAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
    
    if (EffSaveRootFile_) dbe->save(EffRootFileName_);
    
}

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
RecHitAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
RecHitAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RecHitAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RecHitAnalyzer);
