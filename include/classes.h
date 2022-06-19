#ifndef CLASSES_H
#define CLASSES_H 


class Simulation
{

  TH1F *m_q0 {};
  float m_q0Max {};
  TH1F *m_qe {};
  float m_qeMax {};
  TH1F *m_2p2h {};
  float m_2p2hMax {};
  TF1 *m_fitQ0 {};
  bool m_simCheck {};
  
 public:  
  void setQ0(TH1F *simQ0){
    m_q0 = (TH1F*)simQ0->Clone();
  }
  void setQE(TH1F *simQE){
    m_qe = (TH1F*)simQE->Clone();
  }
  void set2p2h(TH1F *sim2p2h){
    m_2p2h = (TH1F*)sim2p2h->Clone();
  }
  void setfitQ0(TF1 *simFit){
    m_fitQ0 = (TF1*)simFit->Clone();
  }
  void setTruth(bool worked){
    m_simCheck = worked;
  }
  
  TH1F *GetQ0(){
    return m_q0;
  }
  TH1F *GetQE(){
    return m_qe;
  }
  TH1F *Get2p2h(){
    return m_2p2h;
  }
  TF1 *GetFitQ0(){
    return m_fitQ0;
  }

  float GetQ0Max(){
    m_q0Max = m_q0->GetMaximum();
    return m_q0Max;
  }
  float GetQEMax(){
    m_qeMax = m_qe->GetMaximum();
    return m_qeMax;
  }
  float Get2p2hMax(){
    m_2p2hMax = m_2p2h->GetMaximum();
    return m_2p2hMax;
  }

  bool GetTruth(){
    return m_simCheck;
  }

};



#endif
