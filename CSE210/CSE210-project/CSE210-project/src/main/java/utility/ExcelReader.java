package utility;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import org.apache.poi.openxml4j.exceptions.InvalidOperationException;
import org.apache.poi.openxml4j.exceptions.OpenXML4JException;
import org.apache.poi.ss.util.CellReference;
import org.apache.poi.openxml4j.opc.OPCPackage;
import org.apache.poi.openxml4j.opc.PackageAccess;
import org.apache.poi.xssf.eventusermodel.ReadOnlySharedStringsTable;
import org.apache.poi.xssf.eventusermodel.XSSFReader;
import org.xml.sax.SAXException;

/**
 * Reads data from an Excel (.xlsx) file.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li> an OPCPackage instance made from the given Excel file;</li>
 *      <li> a ReadOnlySharedStringsTable instance that enables processing of the Shared Strings table;</li>
 *      <li> a XSSFReader instance ;</li>
 *      <li> a XMLInputFactory instance;</li>
 *      <li> an InputStream instance; and </li>
 *      <li> a XMLStreamReader instance;</li>
 *   </ul> 
 * @author Sahand Sabour
 */

public class ExcelReader {
    private static OPCPackage opcPkg;
    private static ReadOnlySharedStringsTable stringsTable;
    private static XSSFReader xssfReader;
    private static XMLInputFactory xmlInputFactory;
    private static InputStream inputStream;
    private static XMLStreamReader xmlReader;
    
    /**
     * Creates an <code>ExcelReader</code> instance with the given parameter.
     * @param filePath the path of the Excel file that we want to read from
     */
    public ExcelReader(String filePath){
        try {
            opcPkg = OPCPackage.open(filePath, PackageAccess.READ);
            stringsTable = new ReadOnlySharedStringsTable(opcPkg);
            xssfReader = new XSSFReader(opcPkg);
            xmlInputFactory = XMLInputFactory.newInstance();
            inputStream = xssfReader.getSheetsData().next();
            //This xml reader is used to create an xml stream rather than a file stream
            //This is because processing xml is much faster and more memory efficient than processing the Excel file itself
            xmlReader = xmlInputFactory.createXMLStreamReader(inputStream);
        }
        catch (IOException | XMLStreamException | InvalidOperationException | OpenXML4JException | SAXException e){
            System.out.println("Something went wrong when reading the excel file...");
        }
    
    }
    
    /**
     * Reads the data from an Excel file and produces a list of String array (list of rows).
     * @return <code>excelData</code>- list of rows that are read from the Excel file
     * @throws XMLStreamException in case of processing errors
     */
    
    public List<String[]> readExcel() throws XMLStreamException {
        System.out.println("\nReading data from the Excel file...");
        //List of rows (String arrays) that represents the Excel file as a whole
        List<String[]> excelData = new ArrayList<>();
        // Run an iterator that checks all the rows in the file
        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                //If it's a row, get the row data using getRow() and add it to the list
                if (xmlReader.getLocalName().equals("row")) {
                    excelData.add(getRow());
                }
            }
        }
        System.out.println("The data from the Excel file was imported successfully!");
        return excelData;
    }
    
    /**
     * Reads data from an Excel file and produces a String array (a row).
     * @return <code>row</code> - array of cells
     * @throws XMLStreamException in case of processing errors
     */
 
    private String[] getRow() throws XMLStreamException {
        //List of cells (String) that represents a row from the Excel file
        List<String> row = new ArrayList<>();
        //Run an iterator that checks all the cells in the row
        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                //If is 
                if (xmlReader.getLocalName().equals("c")) {
                    //For conversion between Excel style and POI usermodel style
                    CellReference cellReference = new CellReference(xmlReader.getAttributeValue(null, "r"));
                    // If a cell is empty and is not the last cell (usually the favorites and retweets field), set the value of the cell to 0
                    while (row.size() < cellReference.getCol()) {
                        row.add("0");
                    }
                    //get the cell type (t) and accordingly get the value for that cell using getCellValue
                    String cellType = xmlReader.getAttributeValue(null, "t");
                    row.add(getCellValue(cellType));
                }
            } 
            //If all the cells in the row are read
            else if (xmlReader.isEndElement() && xmlReader.getLocalName().equals("row")) {
                break;
            }
        }
        return row.toArray(new String[row.size()]);
    }
 
    /**
     * Reads data from an Excel file and returns a String (the cell).
     * @param cellType the type variable stored in the cell.
     * @return  <code>cell</code> - data of a cell
     * @throws XMLStreamException in case of processing errors
     */
    private String getCellValue(String cellType) throws XMLStreamException {
        //The cell value
        String cell = ""; 
        //Run an iterator to check the values of each cell
        while (xmlReader.hasNext()) {
           xmlReader.next();
           if (xmlReader.isStartElement()) {
               //If the cell is not empty
               if (xmlReader.getLocalName().equals("v")) {
                   //If the cell type is string
                   if (cellType != null && cellType.equals("s")) {
                       //Get the index of that cell to retrieve data from the stringsTable
                       int index = Integer.parseInt(xmlReader.getElementText());
                       cell= stringsTable.getItemAt(index).toString();
                   } 
                   else {
                       //Read the contents if its a text-only element
                       cell = xmlReader.getElementText();
                   }
               }
           } 
           //In case the cell value was read 
           else if (xmlReader.isEndElement() && xmlReader.getLocalName().equals("c")) {
               break;
           }
        }
        return cell;
    }
}
