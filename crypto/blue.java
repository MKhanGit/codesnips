//Mohsin Khan
//December 14, 2016
//BLUE Numbers station decoder	

//This program takes as input the weather and numbers from codes 
//transmitted at the end of several recordings found in 20███
//near the ███████ at ███████

//Sample input (command line): 
//$ java blue CLOUDY 10 16 26 6 18 - 4 20 26 1 - 14 11 3 - 8 6 8 15 21 3
//
//The first argument should be the weather (with capitalization...for now...) followed by the numbers station transmission. 
//Number packets can be separated by non-numeric characters if desired, which will separate the decoded words by spaces.

import java.io.*;


public class blue{

public static void main(String []args){
	String weather;	
	int plainOrd;	//plaintext integer holder
	int j;			//modulus divider to loop back keyword 
	int cT = 0;		//cyptotext integer holder
	int kT = 0;		//keytext integer holder
	int sCount = 1; //count number of spaces to keep keyword rotation offset working

	// Hello World statement, for debugging
	//System.out.println("Hosts are friends, not fodder :)");

		try{
			weather = args[0];
			j = weather.length();

			// Test loop to see if keyword rotation loop is working as expected
			
			// for (int i=0;i<args.length - 1;i++){
			// System.out.print(weather.charAt(i%j));
			// 	}

			//System.out.println(" ");


			for (int i=1; i < args.length; i++){
				try{

					cT = Integer.parseInt(args[i]);
					kT = (int)weather.charAt((i-sCount)%j) - 64;

					if (cT >= kT){
						plainOrd = cT - kT + 65;
							}
					else{
						plainOrd =  91 + cT - kT;
							}
					
					System.out.print((char)plainOrd);

					}

				catch(Exception e){
					System.out.print(" ");
					sCount++;
						}
				
					}
			

			System.out.println("\n");
			// System.out.println(args[0]);
			// System.out.println((int)(args[0].charAt(0)));
			// System.out.println( (char)( Integer.parseInt(args[0]) + 64) );
			}
		catch(Exception e){
			System.out.println("ANALYSIS: Invalid argument(s)");
			e.printStackTrace();

		}
	}

}


