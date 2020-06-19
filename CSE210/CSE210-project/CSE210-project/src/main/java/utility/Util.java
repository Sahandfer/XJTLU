package utility;

import java.util.Scanner;

/**
 * This is a Utility class, used to print the UI, get input from the program user, and process input data.
 * 
 * @author Sahand Sabour
 */


public class Util {
    static Scanner keyboard= new Scanner(System.in);
    /**
     * Displays the UI (menu)
     */
    public static void showMenu(){
        System.out.println("* Please Choose one of the following items (type in 1-5)>\n"
                    + "1. Display the top 10 tweets\n"
                    + "2. Display the top 10 users\n"
                    + "3. Keyword seatch \n"
                    + "4. Full text search\n"
                    + "5. Program guide and notes\n"
                    + "6. Exit the program");
    }
    
    /**
     * Displays a user guide on how to use the program (tips and notes)
     */
    public static void showGuide(){
        System.out.println("\n"+"=".repeat(100));
        System.out.println("* The program guide is as follows>\n"
                        + "Enter 1 ==> the program would display the top ten tweets based on the number of the tweet's favorites+ retweets\n"
                        + "Enter 2 ==> the program would display the top ten users based on the number of ther user's followers\n"
                        + "Enter 3 ==> the program performs a basic search amongst all of the tweets in the given Excel file for the entered keyword\n"
                        + "Enter 4 ==> the program performs a full-text search amongst all of the tweets in the given Excel file for the entered keyword or sentence\n"
                        + "Enter 5 ==> the program displays the guide that you are reading at the moment\n"
                        + "Enter 6 ==> the program shuts down \n"
                        + "\n*NOTE* The full-text search only shows the top 15 matching searches, whereas the basic search shows all of the findings!\n"
                        + "\n*NOTE* If you choose to search for a keyword, the results would differ when performing a basic text search compared to to full-text search!\n"
                        + "The program searches for the keyword in full-text search whereas the basic search finds any occurance of the keyword.\n"
                        + "*Example* searching the keyword \"for\" would match \"before\" in basic search but not in the full-text search\n"
                
                        + "\n<=I hope you enjoy using this program=>\n"
                            );
        System.out.println("=".repeat(100)+"\n");
    }
    
    /**
     * Gets input from the user and returns an integer from 1-6.
     * 
     * @return <code>int result</code> - an integer from 1-6
     */
    public static int getIntInput(){
        boolean invalidInput= true;
        int result=0;
        while (invalidInput){
            try{
               result= keyboard.nextInt();
               if (result>0 && result<7) invalidInput= false;
               else System.out.println("Invalid input! Please try again...\n"); 
               keyboard.nextLine();
            }
            catch (Exception e){
                System.out.println("Invalid input! Please try again...\n");
                keyboard.nextLine();
            }
        }
        return result;
    }
    
    /**
     * Gets input from the user and returns a string corresponding to the requirement.
     * 
     * @param  isKeyword true means the input should be one word only
     * @return <code>String result</code> - the processed user input
     */
    public static String getStrInput(boolean isKeyword){
       boolean invalidInput= true;
       String result="";
    
       while(invalidInput){
           try{
               System.out.print("* Please enter a keyword: ");
               result= keyboard.nextLine().trim();
               if (!result.isEmpty()) invalidInput= false;
               else System.out.println("Input cannot be empty! Please try again...\n"); 
           }
           catch (Exception e){
               System.out.println("Invalid input! Please try again...\n");
           }
       }
       if(isKeyword) result= result.split(" ")[0];
       return result;
    }
    
    /**
      * Checks and processes the given string for illegal characters (Mainly for use in Lucene parser)
      * 
      * @param  str the string to be processed 
      * @return <code>String str</code> - the processed string
      */
    public static String checkString(String str){
       String[] illegalChars= {"\\","+","-","&&", "||", "!", "(", ")" ,"{", "}", "[", "]", "^,","\"","~", "*", "?", ":" , "/"};
        for (String illegalChar : illegalChars) {
            if (str.contains(illegalChar)) {
                str= str.replace(illegalChar, '\\'+illegalChar);
            }
        }
       return str;
    }
    

}
