#include <sys/errno.h>
#include <stdio.h>
#include <stdexcept>

#define SBB_LINE_BUFFER_LENGTH 256
#define SBB_INSTRUMENT_ID_LENGTH 32
#define SBB_INSTRUMENT_TICKER_LENGTH 8
#define SBB_INSTRUMENT_RATETYPE_LENGTH 24
#define SBB_INSTRUMENT_QUALITY_LENGTH 12

// wide open class for loading data per instrument
class SBB_instrument_fields {
	public:
		SBB_instrument_fields(){
			SecurityID[0]=0;
            Ticker[0]=0;
			SettlementDate=0;
			CouponRate=0.0;
			MaturityDate=0;
			Frequency=0;
            RateType[0]=0;
			Rate=0.0;
            Quality[0]=0;
            Amount=0;
		} 
		~SBB_instrument_fields() {};

		void show(){
			printf("ID: %s Ticker: %s SettleDate: %d Coupon: %.2f MatDate: %d Frequency: %d RateType: %s Rate: %.3f Quality: %s Amount: %d\n",
				SecurityID,
                Ticker,
				SettlementDate,
				CouponRate,
				MaturityDate,
				Frequency,
                RateType,
				Rate,
                Quality,
                Amount);
		}

		char SecurityID[SBB_INSTRUMENT_ID_LENGTH];
        char Ticker[SBB_INSTRUMENT_TICKER_LENGTH];
		int SettlementDate;
		double CouponRate;
		int MaturityDate;
		short Frequency;
        char RateType[SBB_INSTRUMENT_RATETYPE_LENGTH];
		double Rate;
        char Quality[SBB_INSTRUMENT_QUALITY_LENGTH];
        int Amount;
};

// simple class for interfacing with data file that contains instrument desriptive data 
// (and yield)
class SBB_instrument_input_file {

	// Resource (file handle) acquisition is initialization version - "RAII"
	// destructor closes file...
	public:
		SBB_instrument_input_file(const char* filename);
		~SBB_instrument_input_file();

		//
		// once his object is contructed (and the file is open), returns number of items in it
		//
		int get_record_count();
	
		//
		// returns a heap allocated array of file contents
		//
		SBB_instrument_fields* get_records(int& length);
			
		//
		// As a convenience to the caller memory is allocated inside this class
		// Call this to free it
		//
		void free_records();

	private:
		std::FILE* _file;
		char _line_buf[SBB_LINE_BUFFER_LENGTH];
		SBB_instrument_fields *_fields_array;
	 
		//
		// prevent copying
		// 
		SBB_instrument_input_file (const SBB_instrument_input_file &);
		
		//
		// prevent assignment
		//
		SBB_instrument_input_file & operator= (const SBB_instrument_input_file &);

		//
		// disable the default constructor
		// force construction with filename param only...
		//
		SBB_instrument_input_file();
};
