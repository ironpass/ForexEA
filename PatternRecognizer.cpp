#include <iostream>
using namespace std;

class PatternRecognizer {

  string *Date;
  string *Time;
  double *Open;
  double *High;
  double *Low;
  double *Close;
  double *Volume;

  int testing_length = 6000;
  string buyPattern[1000][2];
  string sellPattern[1000][2];

  public: void detectPattern() {
	  backtest();

	  //Find best buy pattern
	  int maxBuyScore = buyPattern[0][1].length();
	  string bestBuyPattern = buyPattern[0][0];
	  for (int i = 0;i<1000;i++) {
		  if (buyPattern[i][1].length()>maxBuyScore) {
			  maxBuyScore = buyPattern[i][1].length();
			  bestBuyPattern = buyPattern[i][0];
		  }
	  }

	  //Find best sell pattern
	  int maxSellScore = sellPattern[0][1].length();
	  string bestSellPattern = sellPattern[0][0];
	  for (int i = 0;i<1000;i++) {
		  if (sellPattern[i][1].length()>maxSellScore) {
			  maxSellScore = sellPattern[i][1].length();
			  bestSellPattern = sellPattern[i][0];
		  }
	  }

	  //Print the best patterns
	  cout << "Best Buy Pattern: " << bestBuyPattern << " at Score: " << maxBuyScore << "\n";
	  cout << "Best Sell Pattern: " << bestSellPattern << " at Score: " << maxSellScore << "\n";


  }
  void backtest() {
	  for (int i = testing_length;i>0;i--) {
		  
		  if(isStairD(i)){
			string pattern = patternRecognize(i+3);
			addToSellPatternList(pattern);
		  } else if (isStairU(i)) {
			string pattern = patternRecognize(i+3);
			 addToBuyPatternList(pattern);
		  }
		  
		  /*
		  if (isPillarD(i)) {
			  string pattern = patternRecognize(i + 1);
			  addToSellPatternList(pattern);
		  }
		  else if (isPillarU(i)) {
			  string pattern = patternRecognize(i + 1);
			  addToBuyPatternList(pattern);
		  }
		  */

	  }
  }

  bool isStairD(int idx) {
	  if (Close[idx]<Close[idx + 1] && Close[idx + 1]<Close[idx + 2]
		  && Close[idx]<Open[idx]
		  && Close[idx + 1]<Open[idx + 1]
		  && Close[idx + 2]<Open[idx + 2]) {
		  return true;
	  }
	  return false;
  }
  bool isStairU(int idx) {
	  if (Close[idx]>Close[idx + 1] && Close[idx + 1]>Close[idx + 2]
		  && Close[idx]>Open[idx]
		  && Close[idx + 1]>Open[idx + 1]
		  && Close[idx + 2]>Open[idx + 2]) {
		  return true;
	  }
	  return false;
  }

  bool isPillarD(int idx) {
	  if (Open[idx] - Close[idx] >= 0.200)
		  return true;
	  return false;
  }
  bool isPillarU(int idx) {
	  if (Close[idx] - Open[idx] >= 0.200)
		  return true;
	  return false;
  }

  string patternRecognize(int i) {
	  string result = "";
	  if (High[i]>High[i + 1]) result += "1 ";
	  if (High[i]>Open[i + 1]) result += "2 ";
	  if (High[i]>Close[i + 1]) result += "3 ";
	  if (High[i]>Low[i + 1]) result += "4 ";
	  if (Open[i]>High[i + 1]) result += "5 ";
	  if (Open[i]>Open[i + 1]) result += "6 ";
	  if (Open[i]>Close[i + 1]) result += "7 ";
	  if (Open[i]>Low[i + 1]) result += "8 ";
	  if (Close[i]>High[i + 1]) result += "9 ";
	  if (Close[i]>Open[i + 1]) result += "10 ";
	  if (Close[i]>Close[i + 1]) result += "11 ";
	  if (Close[i]>Low[i + 1]) result += "12 ";
	  if (Low[i]>High[i + 1]) result += "13 ";
	  if (Low[i]>Open[i + 1]) result += "14 ";
	  if (Low[i]>Close[i + 1]) result += "15 ";
	  if (Low[i]>Low[i + 1]) result += "16 ";

	  return result;
  }

  void addToBuyPatternList(string pattern) {
	  for (int i = 0;i<1000;i++) {
		  if (pattern.compare(buyPattern[i][0]) == 0) {
			  buyPattern[i][1] += "1";
			  return;
		  }
	  }
	  for (int i = 0;i<1000;i++) {
		  if (buyPattern[i][0].compare("") == 0) {
			  buyPattern[i][0] = pattern;
			  buyPattern[i][1] += "1";
			  break;
		  }
	  }
  }
  void addToSellPatternList(string pattern) {
	  for (int i = 0;i<1000;i++) {
		  if (pattern.compare(sellPattern[i][0]) == 0) {
			  sellPattern[i][1] += "1";
			  return;
		  }
	  }
	  for (int i = 0;i<1000;i++) {
		  if (sellPattern[i][0].compare("") == 0) {
			  sellPattern[i][0] = pattern;
			  sellPattern[i][1] += "1";
			  break;
		  }
	  }
  }


  public: void passBarValues(string *dateP, string *timeP, double *openP, double *highP, double *lowP, double *closeP, double *volumeP) {
	Date = dateP;
	Time = timeP;
	Open = openP;
	High = highP;
	Low = lowP;
	Close = closeP;
	Volume = volumeP;
  }

};
