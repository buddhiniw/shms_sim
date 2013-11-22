/*
Author - B.Waidyawansa
Date - 10/29/2013

A macro to open the shms_sim.root file and draw the following;

1. Hits on the xy, xz and yz planes of the coils differentiated by particle type
 red- electrons
 blue  - positrons
 green - gamma
 purple - neutrons


*/


void draw_hits(TString file, TString ntuple_name)
{
 
  //Delete all the objects stored in the current directory memory
  gDirectory->Delete("*");
  gStyle->SetCanvasPreferGL(1);
  gStyle->SetPalette(1); 

  // pads parameters
  gStyle->SetPadColor(0); 
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadTopMargin(0.12);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.08);  
  gStyle->SetPadRightMargin(0.18);  
  gStyle->SetTitleSize(0.05);


  // Open and chain the root file
  Char_t filename[200]; 
  sprintf(filename,"~/rootfiles/%s_ntuple.root",file.Data());

  TChain * chain = new TChain(ntuple_name);
  TFile *f = new TFile(filename);
  if (f->IsZombie()) {
    std::cout << "Error opening root file chain "<< filename << std::endl;
    exit(1);
  }
  else{
    sprintf(filename,"~/rootfiles/%s_ntuple.root",file.Data());
    std::cout << "Opening root file "<< filename << std::endl;
    chain->Add(filename);
    if(chain == NULL){
      std::cout<< "Unable to find the ntuple " <<ntuple_name<< std::endl; 
      exit(1);
    }
    else{
      std::cout<<"Obtaining data from ntuple : "<<ntuple_name<<"\n";
     
      // Create a canvas 
      TCanvas * C = new TCanvas("canvas","",1300,1000);
      C->Divide(2,2);
      C->SetFillColor(0);
      

      // Get the total number of electrons used for the simulation 
      // from the energy deposition histogram
      // for now hard code the number of events
      Double_t Ne = 20000;
      std::cout<<" Number of beam electrons used for the simulation - "<<Ne<<std::endl;
 
      // Draw total heat deposition in Watt/muA
      C->cd(1);
      TString convert = Form("eDep_MeV/%f",Ne); 

      chain->Draw(Form("%s >>hist",convert.Data()));
      TH1F* h = (TH1*)(gDirectory->Get("hist"));
      h->SetTitle(Form("Heat Deposited in the %s",ntuple_name.Data()));
      h->GetXaxis()->SetTitle("W#muA^{-1} ");
      h->GetYaxis()->SetTitle("Tracking Steps");
      h->SetFillColor(kGreen-2);
      gPad->SetRightMargin(0.08);
      gPad->SetLogy();
      gPad->Update();

      // get energy
      std::cout<<"Get total energy ..\n"; 

      Double_t entries = 0.0;
      Double_t bins = h->GetNbinsX();
      Double_t val = 0;
      Double_t sum = 0;
      for(Int_t i=0;i<bins;i++) {
	entries = h->GetBinContent(i+1);
	val = (h->GetBinCenter(i+1))* entries;
	sum +=val;
      }
 
      TPaveText *pt = new TPaveText(0.3,0.6,0.85,0.8,"NDC");
      pt->AddText(Form("Total heat deposited = %2.1f W#muA^{-1}",sum));
      pt->Draw();
      gPad->Update();
      gPad->Modified();

      // Draw total heat deposition by particle type
      C->cd(2);
      chain->Draw(Form("%s:scat_angle_deg >> h",convert.Data()),"");
      TH2F* ha = (TH2*)(gDirectory->Get("h"));
      ha->SetMarkerColor(kRed-2);
      ha->SetTitle(Form("Heat Deposited in the %s by Scattering Angle at the Vertex",ntuple_name.Data()));
      ha->GetYaxis()->SetTitle("W#muA^{-1} ");
      ha->GetXaxis()->SetTitle("Scattering Angle (deg.)");
      gPad->SetRightMargin(0.08);
      gPad->Update();
      gPad->Modified();


//       // Draw total heat deposition by particle type
//       C->cd(2);
//       chain->Draw(Form("%s >>he",convert.Data()),"flagParticle==1");
//       TH1F* he = (TH1*)(gDirectory->Get("he"));
//       he->SetFillColor(kRed-2);

//       chain->Draw(Form("%s >>hpos",convert.Data()),"flagParticle==2","same");
//       TH1F* hpos = (TH1*)(gDirectory->Get("hpos"));
//       hpos->SetFillColor(kBlue-2);

//       chain->Draw(Form("%s >>hgam",convert.Data()),"flagParticle==3");
//       TH1F* hgam = (TH1*)(gDirectory->Get("hgam"));
//       hgam->SetFillColor(kGreen-2);

//       h3->SetTitle(Form("Heat Deposited in the %s by Particle Type",ntuple_name.Data()));
//       h3->GetXaxis()->SetTitle("W#muA^{-1} ");
//       h3->GetYaxis()->SetTitle("Tracking Steps");
//       gPad->SetRightMargin(0.08);
//       gPad->SetLogy();
//       gPad->Update();



      // Draw total heat deposition on left side
      std::cout<<"Get heat depoisition on left side ..\n"; 
      C->cd(3);
      //chain->Draw(Form("%s:local_z_cm>>left",convert.Data()),"local_x_cm>0","colz");
      chain->Draw("local_y_cm:local_z_cm>>left",Form("%s*(local_x_cm>0)",convert.Data()),"colz");

      TH2F* h1 = (TH2*)(gDirectory->Get("left"));
      h1->SetStats(0);
      h1->SetTitle(Form("Heat deposited along the left side of the %s",ntuple_name.Data()));
      h1->GetYaxis()->SetTitle("Y (cm) ");
      h1->GetXaxis()->SetTitle("Z (cm)");
      gPad->Update();
      TPaletteAxis *palette1 = (TPaletteAxis*)h1->GetListOfFunctions()->FindObject("palette");
      palette1->GetAxis()->SetTitle("W#muA^{-1}");
      palette1->GetAxis()->SetTitleOffset(1.5);
      gPad->Modified();

      // Draw total heat deposition on right side
      std::cout<<"Get heat depoisition on right side ..\n"; 
      C->cd(4);
      //      chain->Draw(Form("%s:local_z_cm>>right",convert.Data()),"local_x_cm<=0","colz");
      chain->Draw("local_y_cm:local_z_cm>>right",Form("%s*(local_x_cm<0)",convert.Data()),"colz");

      TH2F* h2 = (TH2*)(gDirectory->Get("right"));
      h2->SetStats(0);
      h2->SetTitle(Form("Heat deposited along the right side of the %s",ntuple_name.Data()));
      h2->GetYaxis()->SetTitle("Y (cm) ");
      h2->GetXaxis()->SetTitle("Z (cm)");
      gPad->Update();
      TPaletteAxis *palette2 = (TPaletteAxis*)h2->GetListOfFunctions()->FindObject("palette");
      palette2->GetAxis()->SetTitle("W#muA^{-1}");
      palette2->GetAxis()->SetTitleOffset(1.5);
      gPad->Modified();

      // Draw xyz plane
      //      C->cd(4);
      //      std::cout<<"Get heat depoisition on full volume ..\n"; 
  //     chain->Draw(Form("local_y_cm:local_x_cm:local_z_cm:%s >> h3d",convert.Data()),"","glcolz");    
//       TH3D* h3 = (TH3*)(gDirectory->Get("h3d"));
//       h3->SetStats(0);
//       h3->SetTitle(Form("Heat Deposition in the %s Volume",ntuple_name.Data()));
//       h3->GetYaxis()->SetTitle("X (cm)");
//       h3->GetXaxis()->SetTitle("Y (cm)");
//       h3->GetZaxis()->SetTitle("Z (cm)");
//      gPad->Modified();
//      gPad->Update();
    }

    C->Update();
    C->SaveAs(Form("%s_hit_plots.jpg",ntuple_name.Data()));
    //C->SaveAs(Form("%s_hit_plots.C",ntuple_name.Data()));
    std::cout<<"Done!"<<std::endl;
  }
  
  //delete C;

}
