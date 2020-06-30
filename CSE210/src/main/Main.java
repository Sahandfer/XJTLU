package main;

import utility.Searcher;
import utility.Sorter;
import utility.ExcelReader;
import utility.Util;
import lucene.LuceneIndexer;
import java.util.List;
import javax.xml.stream.XMLStreamException;

/**
 * The main part of the program (The entry point).
 * 
 * @see ExcelReader
 * @see Sorter
 * @see LuceneIndexer
 * @author Sahand Sabour
 */

public class Main{
    public static void main(String[] args) throws XMLStreamException {
        //The Excel file to be processed 
        ExcelReader er = new ExcelReader("data/dataset.xlsx");
        //A list that stores all the data from the Excel file in the form of a list of String arrays (list of rows containing cells)
        List<String[]> excelData= er.readExcel();
        // The constructor for this object instantiates the required objects for this program
        Sorter sr= new Sorter(excelData);
        // The constructor for this object creates the required Lucene index files.
        LuceneIndexer li= new LuceneIndexer(sr.getTweets());

        //An integer representing the item that the user has chosen
        int caseNum;
        //A string representing the keyword or the sentence that the user has entered
        String searchWord;
        
        boolean endProgram = false;
        System.out.println("\n===============>WELCOME<===============\n");
        while (!endProgram){
            Util.showMenu();
            caseNum= Util.getIntInput();
            
            switch (caseNum){
                case 1:
                    sr.printTopTweets();
                    break;
                case 2:
                    sr.printTopUsers();
                    break;
                case 3:;
                    searchWord= Util.checkString(Util.getStrInput(true));
                    Searcher.searchKeyword(searchWord, sr.getTweets());
                    break;
                case 4:
                    searchWord= Util.getStrInput(false);
                    Searcher.searchFullText(Util.checkString(searchWord));
                    break;
                case 5:
                    Util.showGuide();
                    break;
                case 6:
                    endProgram= true;
                    break;
                default:
                    System.out.println("\nInvalid choice! Please try again ~");
                    break;
            }
        }
        System.out.println("\nThank you for using my program ~");
        System.out.println("\n============>PROGRAM ENDED<============\n");
    }
}