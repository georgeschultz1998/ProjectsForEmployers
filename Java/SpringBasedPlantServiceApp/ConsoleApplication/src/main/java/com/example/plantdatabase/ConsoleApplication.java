package com.example.plantdatabase;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import java.util.ArrayList;
import java.util.Scanner;
@SpringBootApplication
public class ConsoleApplication {
    private static final Logger log = LoggerFactory.getLogger(ConsoleApplication.class);

    static String strType;
    static final String type0 = "TREE";
    static final String type1 = "PERENNIAL";
    static String result = "";
    static int count = 0;
    static String data = "Users Input";
    static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        SpringApplication.run(ConsoleApplication.class);
    }

    // Variables used through program.
    int menuChoice = -1;
    String nameChoice;
    int typeChoice;
    int zoneChoice;
    String commonName, scienceName;
    int minZone, maxZone, type;

    @Bean
    public CommandLineRunner plantSearchDemo(PlantRepository repository) {
        return (args) -> {
            ArrayList<Plant> plantArray = new ArrayList<>();
            // Start of main menu Loop that does not end until user quits (Enters 0).
            while (menuChoice != 0) {

                // Prints the menu options and asks user to pick one.
                System.out.println("Enter command: ");
                System.out.println("0 to Quit");
                System.out.println("1 to Add");
                System.out.println("2 to Find by type");
                System.out.println("3 to Find by zone");
                System.out.println("4 to Find by name");
                System.out.println("5 to Find all plants");
                System.out.print("> ");
                menuChoice = input.nextInt();

                // ------------------------------------------------------------------
                // if statement for when user chooses to add tree.
                // Stores all user input in temp variables then saves to H2 database.
                if (menuChoice == 1) {
                    System.out.print("Enter the common name of the plant:");

                    input.nextLine();

                    // Stores user input into temporary variables
                    commonName = input.nextLine();
                    System.out.print("Enter the scientific name of the plant:");
                    scienceName = input.nextLine();
                    System.out.print("Enter the minimum planting zone of the plant:");
                    minZone = input.nextInt();
                    System.out.print("Enter the maximum planting zone of the plant:");
                    maxZone = input.nextInt();
                    System.out.print("Enter the type of the plant -- 0 for tree, 1 for perennial:");
                    type = input.nextInt();

                    // Saves the tree using H2 database
                    repository.save(new Plant(commonName, scienceName, minZone, maxZone, type));

                }
                // ----------------------------------------------------------------------

                // ----------------------------------------------------------------------
                // If statement for when user chooses to find tree by type.
                if (menuChoice == 2) {
                    // Fetches all Plants based on plant type
                    System.out.println("Enter the int to match (Ex: 0 for Tree, 1 for Perennial): ");
                    typeChoice = input.nextInt();
                    System.out.println("--------------------------------");
                    System.out.println("Plants that might interest you:");
                    // Calls repository function which finds by plant type then outputs result.
                    repository.searchPlantType(typeChoice).forEach(treeType -> {
                        System.out.println(treeType.toString());
                    });
                    System.out.println("");
                    System.out.println("--------------------------------");
                }
                // ----------------------------------------------------------------------

                // ----------------------------------------------------------------------
                // if statement for when user chooses to find tree by zone. Searches tree zone
                // data and compares it to user input to find matches.
                if (menuChoice == 3) {
                    System.out.println("Enter the zone int to match: (Ex: 5 for zone 5) ");
                    zoneChoice = input.nextInt();
                    // fetch Plant by min zone
                    System.out.println("--------------------------------");
                    System.out.println("Plants that might interest you:");
                    // Calls repository function which finds plants that can grow within the zone
                    // specified by user.
                    repository.searchZone(zoneChoice).forEach(zoneChoice->
                    {System.out.println(zoneChoice.toString());});


            /*
            repository.findByMinZoneLessThanEqualAndMaxZoneGreaterThanEqual(zoneChoice, zoneChoice).forEach(zone -> {
                System.out.println(zone.toString());
            });
             */
                    System.out.println("");
                    System.out.println("--------------------------------");
                }
                // ----------------------------------------------------------------------

                // ----------------------------------------------------------------------
                // if statement for when user chooses to find tree by common name. Searches tree
                // names
                // data and compares it to user input to find matches.
                if (menuChoice == 4) {
                    System.out.println("Enter the string to match: (Ex: Red for Redwood) ");
                    input.nextLine();
                    nameChoice = input.nextLine();
                    System.out.println("--------------------------------");
                    System.out.println("Plants that might interest you:");
                    // Calls repository function which finds plants based on the upper case version
                    // of their common name. Converts user input to upper case as well so original
                    // casing of input or common name does not matter.
                    repository.searchComName(nameChoice).forEach(commonName->
                    {System.out.println(commonName.toString());});

            /*
            repository.findByComNameUpperCaseContains(nameChoice.toUpperCase()).forEach(comname -> {
                System.out.println(comname.toString());
            });
            */
                    System.out.println("");
                    System.out.println("--------------------------------");
                }
                // ----------------------------------------------------------------------

                // ----------------------------------------------------------------------
                if (menuChoice == 5) {
                    // fetch all plants
                    System.out.println("--------------------------------");
                    System.out.println("Plants that might interest you:");
                    for (Plant plant : repository.findAll()) {
                        System.out.println(plant.toString());
                    }
                    System.out.println("");
                    System.out.println("--------------------------------");
                }
                // ----------------------------------------------------------------------
            }
            input.close();
            System.exit(0);

        }; //commandlinerunner

    }// consoleapplication

}
