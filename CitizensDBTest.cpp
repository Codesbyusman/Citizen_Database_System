#include "gtest/gtest.h"
#include "CitizensDatabase.h"
#include <string.h>


TEST(SearchTest, CBID) {
  
	Database<string> db ("CBID.txt", "CCID.txt");
    
    string s1="Ethel Dorset f 22 Buckfast Street british";
    
    EXPECT_TRUE(db.CBID_Search_by_CNIC(3913)==s1);

}

TEST(SearchTest, CCID) {
  
    Database<string> db("CBID.txt", "CCID.txt");
    
    string s1="Buffy Oxford f 9 Albion Street british kidnapping 5 years in prison 15000";
    
    EXPECT_TRUE(db.CCID_Search_by_CNIC(5742)==s1);

}

TEST(UpdateTest, CBID_Name) {

	Database<string> db("CBID.txt", "CCID.txt");
	
    EXPECT_TRUE(db.updateCBIDName("Alice",9831)==1);
    EXPECT_TRUE(db.updateCBIDName("Doc",9832)==0);
    
}

TEST(UpdateTest, CBID_FName) {

    Database<string> db("CBID.txt", "CCID.txt");
    
    EXPECT_TRUE(db.updateCBIDFName("Kevin",9177)==1);
    EXPECT_TRUE(db.updateCBIDFName("Steve",1234)==0);
    
}

TEST(UpdateTest, CBID_Address) {

    Database<string> db("CBID.txt", "CCID.txt");
    
    EXPECT_TRUE(db.updateCBIDAddress("12 Ann Street",8372)==1);
    EXPECT_TRUE(db.updateCBIDAddress("21 Downing Street",9639)==0);
    
}

TEST(UpdateTest, CBID_Nationality) {

    Database<string> db("CBID.txt", "CCID.txt");
    
    EXPECT_TRUE(db.updateCBIDNationality("Alien",8000)==0);
    EXPECT_TRUE(db.updateCBIDNationality("Alien",9832)==0);
    
}

TEST(CrimeAddTest, CCID) {

    Database<string> db("CBID.txt", "CCID.txt");

    EXPECT_TRUE(db.addCrime(7564,"Robbery", "2 years in prison","1000")==1);
    
    EXPECT_TRUE(db.addCrime(8099,"Kidnapping", "20 years in prison","2000")==0);
}

TEST(CrimeDeleteTest, CCID) {

    Database<string> db("CBID.txt", "CCID.txt");

    EXPECT_TRUE(db.deleteCrime(5960,"burglary", "6 years in prison","7000")==1);
    
    EXPECT_TRUE(db.deleteCrime(4064,"murder", "2 years in prison","10000")==0);
}

TEST(CrimeupdateTest, CCID)
{
    Database<string> db("CBID.txt" , "CCID.txt");
    EXPECT_TRUE(db.updateCrime(1234 , "murder" , "20 years in prison" , "10000") == 1);

    EXPECT_TRUE(db.updateCrime(9630 , "murder" , "20 years in prison" , "10000") == 0);
    
}


int main ( int argc , char ** argv ) 
{

	testing::InitGoogleTest(&argc , argv) ;
	return RUN_ALL_TESTS();

}






