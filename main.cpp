#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

class doctor
{
		private:
			int d_id;									//Identifiacation number of the doctor
			char name[30];
			char spec[30];						//Speciality of the doctor
		public:
			void enter();
			void disp();
			int get__d_id(){return d_id;}
			char *get__name(){return name;}
			char *get__spec(){return spec;}
};

void doctor::enter()
{
		system("cls");
		cout<<"\nEnter Doctor Identification Number :";
		cin>>d_id;
		cin.ignore(5,'\n');
		cout<<"\nEnter Doctor's Name :";
		gets(name);
		cout<<"\nEnter Doctor's Speciality :";
		gets(spec);
}

void doctor::disp()
{
		system("cls");
		cout<<"\nDoctor Identification Number :"<<d_id;
		cout<<"\nDoctor's Name :";
		puts(name);
		cout<<"Doctor's Speciality:";
		puts(spec);
}


class patient
{
		private:
			int p_id;									//Identifiaction number of the patient
			char name[30];
			int d_id;									//Identification number of the doctor treating
		public:
			void enter();
			void disp();
			int get__p_id(){return p_id;}
			char *get__name(){return name;}
			int get__d_id(){return d_id;}
};

void patient::enter()
{
		system("cls");
		cout<<"\nEnter Patient Identification Number :";
		cin>>p_id;
		cin.ignore(5,'\n');
		cout<<"\nEnter Patient's Name :";
		gets(name);
		cout<<"\nEnter Treating Doctor Identifiacation Number :";
		cin>>d_id;
}

void patient::disp()
{
		system("cls");
		cout<<"\nPatient Identification Number :"<<p_id;
		cout<<"\nPatient's Name :";
		puts(name);
		cout<<"Treating Doctor Identification Number :";
		cout<<d_id;
}


fstream fdoc;
fstream fpat("PATIENT.txt",ios::in|ios::out);
			
int main()
{
		lmenu:
		cout<<"\n\n\t\t\tSPECTRUM HEALTHCARE\n\n";
		cout<<"\t\t\t1. Doctor info\n";
		cout<<"\t\t\t2. Patient info\n";
		cout<<"\t\t\t3. Statistics\n";
		cout<<"\t\t\t4. Exit\n\n\n";
		cout<<"\t\t\tEnter your option_  ";
		int op,k;
		cin>>op;
		switch(op)
		{
				int opt;
				case 1:
					ldoc:
					system("cls");
					cout<<"\n\n\t\t\tSPECTRUM HEALTHCARE\n\n";
					cout<<"\t\t\tDOCTOR INFO\n\n";
					cout<<"\t\t\t1. Add new doctor\n";
					cout<<"\t\t\t2. Update existing doctor details\n";
					cout<<"\t\t\t3. Remove a doctor\n";
					cout<<"\t\t\t4. View doctor info\n";
					cout<<"\t\t\t5. Back\n\n\n";
					cout<<"\t\t\tEnter your option_  ";
					cin>>opt;
					switch(opt)
					{	
							case 1:											//add new doctor
								fdoc.open("DOCTOR.dat",ios::in|ios::out);
								if(!fdoc)
								{
										cout<<"NOT FOUND";
										system("pause");
										goto ldoc;
								}
								fdoc.seekp(0,ios::end);
								doctor doc1;
								doc1.enter();
								fdoc.write((char*)&doc1,sizeof(doc1));
								if(fdoc.bad())
								{
										cout<<"ERROR";
										system("pause");
										goto ldoc;
								}
								cout<<"WRITTEN";
								system("pause");
								goto ldoc;
							case 2:										//update doctor details
								system("cls");
								fdoc.open("DOCTOR.dat",ios::in|ios::out);
								if(!fdoc)
								{
										cout<<"NOT FOUND";
										system("pause");
										goto ldoc;
								}
								cout<<"\n\n\t\t\tSPECTRUM HEALTHCARE\n\n";
								cout<<"\t\t\tUPDATE\n\n";
								cout<<"Enter Doctor Identification Number :";
								int i;
								cin>>i;
								fdoc.seekp(0,ios::beg);
								k=0;
								while(!fdoc.eof())
								{
										if(fdoc.eof())
										{
												break;
										}
										int n;
										n=fdoc.tellg();
										doctor doc2;
										fdoc.read((char*)&doc2,sizeof(doc2));
										if(doc2.get__d_id()==i)
										{
												cout<<"\nOriginal :\n";
												doc2.disp();
												k=1;
												cout<<"\n\n\t Press 0 to go ahead\n\tPress 1 to go back_ ";
												int m;
												cin>>m;
												if(m==1)
												{
														continue;
												}
												cout<<"\nEnter New One's :\n";
												doc2.enter();
												fdoc.seekp(n,ios::beg);
												fdoc.write((char*)&doc2,sizeof(doc2));
												break;
										}
								}
								fdoc.close();
								if(k==0)
								{	
										cout<<"\nNOT FOUND";
										system("pause");
										goto ldoc;
								}
							case 3:										//Removing
								fdoc.open("DOCTOR.dat",ios::in|ios::out);
								system("cls");
								if(!fdoc)
								{
										cout<<"File not found";
										system("pause");
										goto ldoc;
								}
								ofstream tmp;
								tmp.open("tem.dat",ios::out|ios::trunc);
								k=0;
								cout<<"\n\n\t\t\tREMOVE\n\n";
								cout<<"Enter Doctor Identification Number: \n";
								cin>>i;
								fdoc.seekg(0,ios::beg);
								while(!fdoc.eof())
								{
										if(fdoc.eof())
										{
												break;
										}
										fdoc.read((char*)&doc1,sizeof(doc1));
										if(doc1.get__d_id()==i)
										{
												doc1.disp();
												k=1;
												cout<<"Are you sure you want to delete this (yes=1 no=0)? _";
												int n;
												cin>>n;
												if(n==0)
												{
														tmp.write((char*)&doc1,sizeof(doc1));
												}
										}
										else
										{
												tmp.write((char*)&doc1,sizeof(doc1));
										}
								}
								if(k==0)
								{
										cout<<"Doctor not present\n";
										system("pause");
										goto ldoc;
								}
								tmp.close();
								fdoc.close();
								remove("DOCTOR.dat");
								rename("tem.dat","DOCTOR.dat");
								goto ldoc;
							case 4:																//Searching
								
										
												
					}		
					break;
				case 2:					
					lpat:
					system("cls");
					cout<<"\n\n\t\t\tSPECTRUM HEALTHCARE\n\n";
					cout<<"\t\t\tPATIENT INFO\n\n";
					cout<<"\t\t\t1. Add new patient\n";
					cout<<"\t\t\t2. Update existing patient details\n";
					cout<<"\t\t\t3. Remove a patient\n";
					cout<<"\t\t\t4. View patient info\n";
					cout<<"\t\t\t5. Back\n\n\n";
					cout<<"\t\t\tEnter your option_  ";
					cin>>opt;
					switch(opt)
					{
							case 1:												//add new patient
								fpat.open("PATIENT.dat",ios::in|ios::out);
								if(!fpat)
								{
										cout<<"NOT FOUND";
										system("pause");
										goto lpat;
								}
								fpat.seekp(0,ios::end);
								patient pat1;
								pat1.enter();
								fpat.write((char*)&pat1,sizeof(pat1));
								if(fpat.bad())
								{
										cout<<"ERROR";
										system("pause");
										goto ldoc;
								}
								cout<<"WRITTEN";
								system("pause");
								goto lpat;
							case 2:										//update doctor details
								system("cls");
								fpat.open("PATIENT.dat",ios::in|ios::out);
								if(!fpat)
								{
										cout<<"NOT FOUND";
										system("pause");
										goto lpat;
								}
								cout<<"\n\n\t\t\tSPECTRUM HEALTHCARE\n\n";
								cout<<"\t\t\tUPDATE\n\n";
								cout<<"Enter Patient Identification Number :";
								int i;
								cin>>i;
								fpat.seekp(0,ios::beg);
								k=0;
								while(!fpat.eof())
								{
										if(fpat.eof())
										{
												break;
										}
										int n;
										n=fpat.tellg();
										patient pat2;
										fpat.read((char*)&pat2,sizeof(pat2));
										if(pat2.get__p_id()==i)
										{
												cout<<"\nOriginal :\n";
												pat2.disp();
												k=1;
												cout<<"\n\n\t Press 0 to go ahead\n\tPress 1 to go back_ ";
												int m;
												cin>>m;
												if(m==1)
												{
														continue;
												}
												cout<<"\nEnter New One's :\n";
												pat2.enter();
												fpat.seekp(n,ios::beg);
												fpat.write((char*)&pat2,sizeof(pat2));
												break;
										}
								}
								fpat.close();
								if(k==0)
								{	
										cout<<"\nNOT FOUND";
										system("pause");
										goto lpat;
								}
							case 3:										//Removing
								fpat.open("PATIENT.dat",ios::in|ios::out);
								system("cls");
								if(!fpat)
								{
										cout<<"File not found";
										system("pause");
										goto lpat;
								}
								ofstream tmp;
								tmp.open("tem.dat",ios::out|ios::trunc);
								k=0;
								cout<<"\n\n\t\t\tREMOVE\n\n";
								cout<<"Enter PATIENT Identification Number: \n";
								cin>>i;
								fdoc.seekg(0,ios::beg);
								while(!fpat.eof())
								{
										if(fpat.eof())
										{
												break;
										}
										fpat.read((char*)&pat1,sizeof(pat1));
										if(pat1.get__p_id()==i)
										{
												pat1.disp();
												k=1;
												cout<<"Are you sure you want to delete this (yes=1 no=0)? _";
												int n;
												cin>>n;
												if(n==0)
												{
														tmp.write((char*)&pat1,sizeof(pat1));
												}
										}
										else
										{
												tmp.write((char*)&pat1,sizeof(pat1));
										}
								}
								if(k==0)
								{
										cout<<"Patient not present\n";
										system("pause");
										goto lpat;
								}
								tmp.close();
								fpat.close();
								remove("PATIENT.dat");
								rename("tem.dat","PATIENT.dat");
								goto lpat;
							
					}
					break;
				case 3:
					break;
				case 4:
					break;
		}
		return 0;
}