import FWCore.ParameterSet.Config as cms
from DQMServices.Core.DQMEDHarvester import DQMEDHarvester

###############Same flavour dilepton with dz cuts#######################
ele23Ele12CaloIdLTrackIdLIsoVL_effdz = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/DiLepton/HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1        'efficiency vs lead electron pt; electron pt [GeV]; efficiency' elePt_1_numerator       elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs lead electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs lead electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs lead electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator       elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning      'efficiency vs lead electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1       'efficiency vs lead electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1      'efficiency vs lead electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
        "effic_elePt_2       'efficiency vs sub-lead electron pt; electron pt [GeV]; efficiency' elePt_2_numerator       elePt_2_denominator",
        "effic_eleEta_2       'efficiency vs sub-lead electron eta; electron eta ; efficiency' eleEta_2_numerator       eleEta_2_denominator",
        "effic_elePhi_2       'efficiency vs sub-lead electron phi; electron phi ; efficiency' elePhi_2_numerator       elePhi_2_denominator",
        "effic_elePt_2_variableBinning       'efficiency vs sub-lead electron pt; electron pt [GeV]; efficiency' elePt_2_variableBinning_numerator       elePt_2_variableBinning_denominator",
        "effic_eleEta_2_variableBinning       'efficiency vs sub-lead electron eta; electron eta ; efficiency' eleEta_2_variableBinning_numerator       eleEta_2_variableBinning_denominator",
        "effic_elePtEta_2       'efficiency vs sub-lead electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_2_numerator       elePtEta_2_denominator",
        "effic_eleEtaPhi_2      'efficiency vs sub-lead electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_2_numerator       eleEtaPhi_2_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
        "effic_ElectronPt_vs_LS 'Lead electron p_T efficiency vs LS; LS; Electron p_T efficiency' eleVsLS_numerator eleVsLS_denominator"
    ),
)



################################MuEG cross triggers###################################
mu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZ_effele =  DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/DiLepton/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/eleLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_numerator       elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator       elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1       'efficiency vs electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1       'efficiency vs electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
    	"effic_ElectronPt_vs_LS 'Electron p_T efficiency vs LS; LS; Electron p_T efficiency' eleVsLS_numerator eleVsLS_denominator"
    ),
)

mu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZ_effmu = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/DiLepton/HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/muLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator       muPtEta_1_denominator",
        "effic_muEtaPhi_1       'efficiency vs muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator       muEtaPhi_1_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
        "effic_MuonPt_vs_LS 'Muon p_T efficiency vs LS; LS; Muon p_T efficiency' muVsLS_numerator muVsLS_denominator"
    ),
)

mu12TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZ_effele =  DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/DiLepton/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/eleLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_numerator       elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator       elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1       'efficiency vs electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1       'efficiency vs electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
    	"effic_ElectronPt_vs_LS 'Electron p_T efficiency vs LS; LS; Electron p_T efficiency' eleVsLS_numerator eleVsLS_denominator"
    ),
)

mu12TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZ_effmu = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/DiLepton/HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/muLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator       muPtEta_1_denominator",
        "effic_muEtaPhi_1       'efficiency vs muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator       muEtaPhi_1_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
        "effic_MuonPt_vs_LS 'Muon p_T efficiency vs LS; LS; Muon p_T efficiency' muVsLS_numerator muVsLS_denominator"
    ),
)

##########################Triple Electron################################3##
ele16ele12ele8caloIdLTrackIdL =  DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs lead electron pt; electron pt [GeV]; efficiency' elePt_1_numerator	elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs lead electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs lead electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1�_variableBinning       'efficiency vs lead electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator	elePt_1variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs lead electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1	'efficiency vs lead electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1	 'efficiency vs lead electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
        "effic_elePt_2       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_numerator	elePt_2_denominator",
        "effic_eleEta_2       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_numerator       eleEta_2_denominator",
        "effic_elePhi_2       'efficiency vs sub-leading electron phi; electron phi ; efficiency' elePhi_2_numerator       elePhi_2_denominator",
        "effic_elePt_2_variableBinning       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_variableBinning_numerator	elePt_2_variableBinning_denominator",
        "effic_eleEta_2_variableBinning       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_variableBinning_numerator       eleEta_2_variableBinning_denominator",
        "effic_elePtEta_2	'efficiency vs sub-leading electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_2_numerator       elePtEta_2_denominator",
        "effic_eleEtaPhi_2	 'efficiency vs sub-leading electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_2_numerator       eleEtaPhi_2_denominator",
        "effic_elePt_3       'efficiency vs trailing electron pt; electron pt [GeV]; efficiency' elePt_3_numerator       elePt_3_denominator",
        "effic_eleEta_3       'efficiency vs trailing electron eta; electron eta ; efficiency' eleEta_3_numerator       eleEta_3_denominator",
        "effic_elePhi_3       'efficiency vs trailing electron phi; electron phi ; efficiency' elePhi_3_numerator       elePhi_3_denominator",
        "effic_elePt_3_variableBinning       'efficiency vs trailing electron pt; electron pt [GeV]; efficiency' elePt_3_variableBinning_numerator       elePt_3_variableBinning_denominator",
        "effic_eleEta_3_variableBinning       'efficiency vs trailing electron eta; electron eta ; efficiency' eleEta_3_variableBinning_numerator       eleEta_3_variableBinning_denominator",
        "effic_elePtEta_3       'efficiency vs trailing electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_3_numerator       elePtEta_3_denominator",
        "effic_eleEtaPhi_3       'efficiency vs trailing electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_3_numerator       eleEtaPhi_3_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
    	"effic_LeadElectronPt_vs_LS 'Electron p_T efficiency vs LS; LS; Electron p_T efficiency' eleVsLS_numerator eleVsLS_denominator"
    ),
)

################################Triple Muon##########################
triplemu12mu10mu5 = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_TripleMu_12_10_5/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs leading muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator	muPtEta_1_denominator",
        "effic_muEtaPhi_1	'efficiency vs leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator	 muEtaPhi_1_denominator",
        "effic_muPt_2       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_numerator       muPt_2_denominator",
        "effic_muEta_2       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_numerator       muEta_2_denominator",
        "effic_muPhi_2       'efficiency vs sub-leading muon phi; muon phi ; efficiency' muPhi_2_numerator       muPhi_2_denominator",
        "effic_muPt_2_variableBinning       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_variableBinning_numerator       muPt_2_variableBinning_denominator",
        "effic_muEta_2_variableBinning       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_variableBinning_numerator       muEta_2_variableBinning_denominator",
        "effic_muPtEta_2       'efficiency vs sub-leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_2_numerator	muPtEta_2_denominator",
        "effic_muEtaPhi_2	'efficiency vs sub-leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_2_numerator	 muEtaPhi_2_denominator",
        "effic_muPt_3       'efficiency vs trailing muon pt; muon pt [GeV]; efficiency' muPt_3_numerator       muPt_3_denominator",
        "effic_muEta_3       'efficiency vs trailing muon eta; muon eta ; efficiency' muEta_3_numerator       muEta_3_denominator",
        "effic_muPhi_3       'efficiency vs trailing muon phi; muon phi ; efficiency' muPhi_3_numerator       muPhi_3_denominator",
        "effic_muPt_3_variableBinning       'efficiency vs trailing muon pt; muon pt [GeV]; efficiency' muPt_3_variableBinning_numerator       muPt_3_variableBinning_denominator",
        "effic_muEta_3_variableBinning       'efficiency vs trailing muon eta; muon eta ; efficiency' muEta_3_variableBinning_numerator       muEta_3_variableBinning_denominator",
        "effic_muPtEta_3       'efficiency vs trailing muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_3_numerator	muPtEta_3_denominator",
        "effic_muEtaPhi_3	'efficiency vs trailing muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_3_numerator	 muEtaPhi_3_denominator",
    ),
    efficiencyProfile = cms.untracked.vstring(
        "effic_LeadMuonPt_vs_LS 'Muon p_T efficiency vs LS; LS; Muon p_T efficiency' muVsLS_numerator muVsLS_denominator"
    ),
)

#############################Double Mu + Single Ele######################################
dimu9ele9caloIdLTrackIdLdz_effmu = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_DiMu9_Ele9_CaloIdL_TrackIdL/muLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs leading muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator	muPtEta_1_denominator",
        "effic_muEtaPhi_1      'efficiency vs leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator	muEtaPhi_1_denominator",
        "effic_muPt_2       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_numerator       muPt_2_denominator",
        "effic_muEta_2       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_numerator       muEta_2_denominator",
        "effic_muPhi_2       'efficiency vs sub-leading muon phi; muon phi ; efficiency' muPhi_2_numerator       muPhi_2_denominator",
        "effic_muPt_2_variableBinning       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_variableBinning_numerator       muPt_2_variableBinning_denominator",
        "effic_muEta_2_variableBinning       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_variableBinning_numerator       muEta_2_variableBinning_denominator",
        "effic_muPtEta_2       'efficiency vs sub-leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_2_numerator	muPtEta_2_denominator",
        "effic_muEtaPhi_2      'efficiency vs sub-leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_2_numerator	muEtaPhi_2_denominator",
    ),
)

dimu9ele9caloIdLTrackIdLdz_effele = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_DiMu9_Ele9_CaloIdL_TrackIdL/eleLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_numerator       elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator       elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1       'efficiency vs electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1       'efficiency vs electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
    ),
)

dimu9ele9caloIdLTrackIdLdz_effdz = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_DiMu9_Ele9_CaloIdL_TrackIdL/dzMon/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs leading muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs leading muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs leading muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator	muPtEta_1_denominator",
        "effic_muEtaPhi_1      'efficiency vs leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator	muEtaPhi_1_denominator",
        "effic_muPt_2       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_numerator       muPt_2_denominator",
        "effic_muEta_2       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_numerator       muEta_2_denominator",
        "effic_muPhi_2       'efficiency vs sub-leading muon phi; muon phi ; efficiency' muPhi_2_numerator       muPhi_2_denominator",
        "effic_muPt_2_variableBinning       'efficiency vs sub-leading muon pt; muon pt [GeV]; efficiency' muPt_2_variableBinning_numerator       muPt_2_variableBinning_denominator",
        "effic_muEta_2_variableBinning       'efficiency vs sub-leading muon eta; muon eta ; efficiency' muEta_2_variableBinning_numerator       muEta_2_variableBinning_denominator",
        "effic_muPtEta_2       'efficiency vs sub-leading muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_2_numerator	muPtEta_2_denominator",
        "effic_muEtaPhi_2      'efficiency vs sub-leading muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_2_numerator	muEtaPhi_2_denominator",
        "effic_elePt_1       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_numerator       elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator       elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1       'efficiency vs electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1       'efficiency vs electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
    ),
)

######Double Electron + Single Muon######
mu8diEle12CaloIdLTrackIdL_effele = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_Mu8_DiEle12_CaloIdL_TrackIdL/eleLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs leading electron pt; electron pt [GeV]; efficiency' elePt_1_numerator	elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs leading electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs leading electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs leading electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator	elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs leading electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1	'efficiency vs leading electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1	 'efficiency vs leading electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
        "effic_elePt_2       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_numerator	elePt_2_denominator",
        "effic_eleEta_2       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_numerator       eleEta_2_denominator",
        "effic_elePhi_2       'efficiency vs sub-leading electron phi; electron phi ; efficiency' elePhi_2_numerator       elePhi_2_denominator",
        "effic_elePt_2_variableBinning       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_variableBinning_numerator	elePt_2_variableBinning_denominator",
        "effic_eleEta_2_variableBinning       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_variableBinning_numerator       eleEta_2_variableBinning_denominator",
        "effic_elePtEta_2	'efficiency vs sub-leading electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_2_numerator       elePtEta_2_denominator",
        "effic_eleEtaPhi_2	 'efficiency vs sub-leading electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_2_numerator       eleEtaPhi_2_denominator",
    ),
) 
mu8diEle12CaloIdLTrackIdL_effmu = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_Mu8_DiEle12_CaloIdL_TrackIdL/muLeg/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_muPt_1       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator       muPtEta_1_denominator",
        "effic_muEtaPhi_1       'efficiency vs muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator       muEtaPhi_1_denominator",
    ),
)

mu8diEle12CaloIdLTrackIdL_effdz = DQMEDHarvester("DQMGenericClient",
    subDirs        = cms.untracked.vstring("HLT/Higgs/TriLepton/HLT_Mu8_DiEle12_CaloIdL_TrackIdL/dzMon/"),
    verbose        = cms.untracked.uint32(0), # Set to 2 for all messages
    resolution     = cms.vstring(),
    efficiency     = cms.vstring(
        "effic_elePt_1       'efficiency vs leading electron pt; electron pt [GeV]; efficiency' elePt_1_numerator	elePt_1_denominator",
        "effic_eleEta_1       'efficiency vs leading electron eta; electron eta ; efficiency' eleEta_1_numerator       eleEta_1_denominator",
        "effic_elePhi_1       'efficiency vs leading electron phi; electron phi ; efficiency' elePhi_1_numerator       elePhi_1_denominator",
        "effic_elePt_1_variableBinning       'efficiency vs leading electron pt; electron pt [GeV]; efficiency' elePt_1_variableBinning_numerator	elePt_1_variableBinning_denominator",
        "effic_eleEta_1_variableBinning       'efficiency vs leading electron eta; electron eta ; efficiency' eleEta_1_variableBinning_numerator       eleEta_1_variableBinning_denominator",
        "effic_elePtEta_1	'efficiency vs leading electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_1_numerator       elePtEta_1_denominator",
        "effic_eleEtaPhi_1	 'efficiency vs leading electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_1_numerator       eleEtaPhi_1_denominator",
        "effic_elePt_2       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_numerator	elePt_2_denominator",
        "effic_eleEta_2       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_numerator       eleEta_2_denominator",
        "effic_elePhi_2       'efficiency vs sub-leading electron phi; electron phi ; efficiency' elePhi_2_numerator       elePhi_2_denominator",
        "effic_elePt_2_variableBinning       'efficiency vs sub-leading electron pt; electron pt [GeV]; efficiency' elePt_2_variableBinning_numerator	elePt_2_variableBinning_denominator",
        "effic_eleEta_2_variableBinning       'efficiency vs sub-leading electron eta; electron eta ; efficiency' eleEta_2_variableBinning_numerator       eleEta_2_variableBinning_denominator",
        "effic_elePtEta_2	'efficiency vs sub-leading electron pt-#eta; electron pt [GeV]; electron #eta' elePtEta_2_numerator       elePtEta_2_denominator",
        "effic_eleEtaPhi_2	 'efficiency vs sub-leading electron #eta-#phi; electron #eta ; electron #phi' eleEtaPhi_2_numerator       eleEtaPhi_2_denominator",
        "effic_muPt_1       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_numerator       muPt_1_denominator",
        "effic_muEta_1       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_numerator       muEta_1_denominator",
        "effic_muPhi_1       'efficiency vs muon phi; muon phi ; efficiency' muPhi_1_numerator       muPhi_1_denominator",
        "effic_muPt_1_variableBinning       'efficiency vs muon pt; muon pt [GeV]; efficiency' muPt_1_variableBinning_numerator       muPt_1_variableBinning_denominator",
        "effic_muEta_1_variableBinning       'efficiency vs muon eta; muon eta ; efficiency' muEta_1_variableBinning_numerator       muEta_1_variableBinning_denominator",
        "effic_muPtEta_1       'efficiency vs muon pt-#eta; muon pt [GeV]; muon #eta' muPtEta_1_numerator       muPtEta_1_denominator",
        "effic_muEtaPhi_1       'efficiency vs muon #eta-#phi; muon #eta ; muon #phi' muEtaPhi_1_numerator       muEtaPhi_1_denominator",
    ),
)

higgsClient = cms.Sequence(
    ele23Ele12CaloIdLTrackIdLIsoVL_effdz
  + dimu9ele9caloIdLTrackIdLdz_effmu 
  + dimu9ele9caloIdLTrackIdLdz_effele 
  + dimu9ele9caloIdLTrackIdLdz_effdz 
  + mu8diEle12CaloIdLTrackIdL_effmu
  + mu8diEle12CaloIdLTrackIdL_effele
  + mu8diEle12CaloIdLTrackIdL_effdz
  + ele16ele12ele8caloIdLTrackIdL
  + triplemu12mu10mu5
  + mu12TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZ_effele
  + mu12TrkIsoVVLEle23CaloIdLTrackIdLIsoVLDZ_effmu
  + mu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZ_effele
  + mu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLDZ_effmu
)
