// Double_t fit_func(Double_t *x, Double_t *par){
//   Float_t xx =x[0];
//   if(xx<par[0])f = par[1]*x+par[2];
//   else f=par[3]*x+par[0]*(par[1]-par[3])+par[2];
//   return f;
// }
{
  int NBINS=32;
    TFile *resfile=new TFile("resolution.root");
  // TFile *resfile=new TFile("resolution_good.root");
  float tibrms[NBINS],tobrms[NBINS],tidrms[NBINS],tecrms[NBINS];
  float tibrmserror[NBINS],tobrmserror[NBINS],tidrmserror[NBINS],tecrmserror[NBINS];
  TH1F *tibres[NBINS],*tobres[NBINS],*tidres[NBINS],*tecres[NBINS];
  TH1F *allres[NBINS];
  float allrms[NBINS],allrmserror[NBINS];
  for(int i=0;i<NBINS;i++){
    TH1F *tibres[i]=(TH1F*)resfile->Get(Form("mTIBresy_%f-%f",i*8./NBINS,i*8./NBINS+8./NBINS));
    TH1F *tobres[i]=(TH1F*)resfile->Get(Form("mTOBresy_%f-%f",i*8./NBINS,i*8./NBINS+8./NBINS));
    TH1F *tidres[i]=(TH1F*)resfile->Get(Form("mTIDresy_%f-%f",i*8./NBINS,i*8./NBINS+8./NBINS));
    TH1F *tecres[i]=(TH1F*)resfile->Get(Form("mTECresy_%f-%f",i*8./NBINS,i*8./NBINS+8./NBINS));
    allres[i]=(TH1F*)tibres[i]->Clone(Form("Allres_%f-%f",i*8./NBINS,i*8./NBINS+8./NBINS));
    allres[i]->Add(tobres[i]);
    allres[i]->Add(tidres[i]);
    allres[i]->Add(tecres[i]);
    tibres[i]->Fit("gaus");
    tobres[i]->Fit("gaus");
    tidres[i]->Fit("gaus");
    tecres[i]->Fit("gaus");
    allres[i]->Fit("gaus");
    tibrms[i]=tibres[i]->GetFunction("gaus")->GetParameter(2);
    tibrmserror[i]=tibres[i]->GetFunction("gaus")->GetParError(2);
    tobrms[i]=tobres[i]->GetFunction("gaus")->GetParameter(2);
    tobrmserror[i]=tobres[i]->GetFunction("gaus")->GetParError(2);
    tidrms[i]=tidres[i]->GetFunction("gaus")->GetParameter(2);
    tidrmserror[i]=tidres[i]->GetFunction("gaus")->GetParError(2);
    tecrms[i]=tecres[i]->GetFunction("gaus")->GetParameter(2);
    tecrmserror[i]=tecres[i]->GetFunction("gaus")->GetParError(2);
    allrms[i]=allres[i]->GetFunction("gaus")->GetParameter(2);
    allrmserror[i]=allres[i]->GetFunction("gaus")->GetParError(2);
  }
  float proj[NBINS],proje[NBINS];
  for (int i=0;i<NBINS;i++){proj[i]=float(i)/4+0.125; proje[i]=0;};
  TGraphErrors *TIB=new TGraphErrors(NBINS,proj,tibrms,proje,tibrmserror);
  TGraphErrors *TOB=new TGraphErrors(NBINS,proj,tobrms,proje,tobrmserror);
  TGraphErrors *TID=new TGraphErrors(NBINS,proj,tidrms,proje,tidrmserror);
  TGraphErrors *TEC=new TGraphErrors(NBINS,proj,tecrms,proje,tecrmserror);
  TGraphErrors *ALL=new TGraphErrors(NBINS,proj,allrms,proje,allrmserror);

//   TProfile *tiberr=(TProfile*)resfile->Get("mTIBsqrterrvsprojy");
//   TProfile *toberr=(TProfile*)resfile->Get("mTOBsqrterrvsprojy");
//   TProfile *tiderr=(TProfile*)resfile->Get("mTIDsqrterrvsprojy");
//   TProfile *tecerr=(TProfile*)resfile->Get("mTECsqrterrvsprojy");
   TProfile *tiberr=(TProfile*)resfile->Get("mTIBtksqrterrvsprojy");
   TProfile *toberr=(TProfile*)resfile->Get("mTOBtksqrterrvsprojy");
   TProfile *tiderr=(TProfile*)resfile->Get("mTIDtksqrterrvsprojy");
   TProfile *tecerr=(TProfile*)resfile->Get("mTECtksqrterrvsprojy");

//   TF1 *errparamtib=new TF1("error_paramtib","((x-[0])*(x-[0])*([1]-[2])/([0]*[0])+[2])",0.01,4);
//   errparamtib->SetParameter(0,38.07*0.032);
//   errparamtib->SetParameter(1,0.3184);
//   errparamtib->SetParameter(2,0.09828);
//   TF1 *errparamtob=new TF1("error_paramtob","((x-[0])*(x-[0])*([1]-[2])/([0]*[0])+[2])",0.01,4);
//   errparamtob->SetParameter(0,38.07*0.05);
//   errparamtob->SetParameter(1,0.3184);
//   errparamtob->SetParameter(2,0.09828);

//   //  TF1 *newparam=new TF1("error_param","(((x-[0])*(x-[0])*([1]-[2])/([0]*[0]))*(([3]-x)/[3])+[2])*(((x-[0])*(x-[0])*([1]-[2])/([0]*[0]))*(([3]-x)/[3])+[2])",0,8); 
//   TF1 *newparam=new TF1("error_param","[0]*x*exp(-x*[1])+[2]",0.,8);
//   //TF1 *newparam=new TF1("error_param","[0]*exp(-0.5*((x-[3])/[1])**2)+[2]*x",0.0001,8);
//   // TF1 *newparam=new TF1("error_param",fit_func,0.0001,8,4);
//   newparam->SetParameter(0,-0.25);
//   newparam->SetParameter(1,1.5);
//   newparam->SetParameter(2,0.3);
//   // newparam->SetParameter(3,0.25);
 
 TCanvas * plot=new TCanvas("resolution","resolution");
  plot->Divide(2,2);
  plot->cd(1);
  TIB->SetMaximum(0.007);
  TIB->SetMinimum(0.);
  TIB->GetHistogram()->GetXaxis()->SetRangeUser(0,4);
  TIB->GetHistogram()->GetXaxis()->SetTitle("Track projection");
  TIB->GetHistogram()->SetTitle("TIB");
  TIB->Draw("ap");
  //  TIB->Fit(newparam);
  TLine *l=new TLine(0,1./sqrt(12),4,1./sqrt(12));
  l->SetLineColor(3);
  l->Draw("same");
  //  errparamtib->SetLineColor(4);
  tiberr->SetMarkerColor(2);
  tiberr->SetLineColor(2);
  tiberr->Draw("same");
  //  tibtkerr->SetMarkerColor(4);
  // tibtkerr->SetLineColor(4);
  // tibtkerr->Draw("same");

  plot->cd(2);
  TOB->SetMaximum(0.007);
  TOB->SetMinimum(0.);
  TOB->GetHistogram()->GetXaxis()->SetRangeUser(0,4);
  TOB->GetHistogram()->GetXaxis()->SetTitle("Track projection");
  TOB->GetHistogram()->SetTitle("TOB");
  TOB->Draw("ap");
  //  TOB->Fit(newparam);
  TLine *l=new TLine(0,1./sqrt(12),4,1./sqrt(12));
  l->SetLineColor(3);
  l->Draw("same");
  toberr->SetMarkerColor(2);
  toberr->SetLineColor(2);
  //  errparamtob->SetLineColor(4);
  toberr->Draw("same");
  //  tobtkerr->SetMarkerColor(4);
  // tobtkerr->SetLineColor(4);
  // tobtkerr->Draw("same");

  plot->cd(3);
  TID->SetMaximum(0.007);
  TID->SetMinimum(0.);
  TID->GetHistogram()->GetXaxis()->SetRangeUser(0,4);
  TID->GetHistogram()->GetXaxis()->SetTitle("Track projection");
  TID->GetHistogram()->SetTitle("TID");
  TID->Draw("ap");
  //  TID->Fit(newparam);
  TLine *l=new TLine(0,1./sqrt(12),4,1./sqrt(12));
  l->SetLineColor(3);
  l->Draw("same");
  //errparamtib->SetLineColor(4);
  tiderr->SetMarkerColor(2);
  tiderr->SetLineColor(2);
  tiderr->Draw("same");
  //  tidtkerr->SetMarkerColor(4);
  //  tidtkerr->SetLineColor(4);
  // tidtkerr->Draw("same");

  plot->cd(4);
  TEC->SetMaximum(0.007);
  TEC->SetMinimum(0.);
  TEC->GetHistogram()->GetXaxis()->SetRangeUser(0,4);
  TEC->GetHistogram()->GetXaxis()->SetTitle("Track projection");
  TEC->GetHistogram()->SetTitle("TEC");
  TEC->Draw("ap");
  //  TEC->Fit(newparam);
  TLine *l=new TLine(0,1./sqrt(12),4,1./sqrt(12));
  l->SetLineColor(3);
  l->Draw("same");
  tecerr->SetMarkerColor(2);
  tecerr->SetLineColor(2);
  tecerr->Draw("same");
  //  tectkerr->SetMarkerColor(4);
  //  tectkerr->SetLineColor(4);
  //  tectkerr->Draw("same");

 TCanvas * plot2=new TCanvas("resolution2","resolution2");
 ALL->SetMaximum(0.01);
 ALL->SetMinimum(0.);
 ALL->Draw("ap");
 // ALL->Fit(newparam);
 TLine *l=new TLine(0,1./sqrt(12),4,1./sqrt(12));
 l->SetLineColor(3);
 l->Draw("same");
}
