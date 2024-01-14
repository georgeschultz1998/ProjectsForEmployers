// Client for hw7 -- command line program to manage list of email contacts

package main

import (
	"bufio"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
)

// port of service where we send requests
var PORT = 8080

// Gets an item name, item details, & its min bid from user.
func add(scanner *bufio.Scanner) {
	fmt.Print("Please enter the item name: ")
	scanner.Scan()
	name := scanner.Text()
	fmt.Print("Please enter the item description: ")
	scanner.Scan()
	desc := scanner.Text()
	fmt.Print("Please enter the minimum Bid: ")
	scanner.Scan()
	minBid := scanner.Text()
	request := fmt.Sprintf("http://localhost:%v/add?name=%v&desc=%v&minBid=%v", PORT, url.PathEscape(name), url.PathEscape(desc), url.PathEscape(minBid))
	resp, err := http.Get(request)
	if err != nil {
		fmt.Printf("%v", err)
		return
	}
	body, err := io.ReadAll(resp.Body)
	response := string(body)
	if response == " " {
		fmt.Println("Response=", response)
	}
}

// Lookup a name in our item list -- names are assumed to be unique
func lookup(scanner *bufio.Scanner) {
	fmt.Print("Please enter the name: ")
	scanner.Scan()
	name := scanner.Text()
	request := fmt.Sprintf("http://localhost:%v/lookup?name=%v",
		PORT, url.PathEscape(name))
	resp, err := http.Get(request)
	if err != nil {
		fmt.Printf("%v", err)
		return
	}
	body, err := io.ReadAll(resp.Body)
	response := string(body)
	if "" == response {
		fmt.Printf("%v is not in the item list\n", name)
	} else {
		fmt.Printf(string(response))
	}
}

// Lookup a name in our item list -- names are assumed to be unique
// Allows user to place bid. Outputs appropriate response to bid.
func bid(scanner *bufio.Scanner, userName string) {

	fmt.Print("Name of item to bid on: ")
	scanner.Scan()
	name := scanner.Text()

	fmt.Print("Amount to bid, in $US: ")
	scanner.Scan()
	amount := scanner.Text()

	request := fmt.Sprintf("http://localhost:%v/bid?name=%v&amount=%v&userName=%v",
		PORT, url.PathEscape(name), url.PathEscape(amount), url.PathEscape(userName))

	resp, err := http.Get(request)
	//fmt.Println("after the request")
	if err != nil {
		fmt.Printf("%v", err)
		return
	}
	body, err := io.ReadAll(resp.Body)
	bidResp := string(body)
	fmt.Printf(bidResp)
}

func main() {
	//client := new(http.Client)

	var cmd string
	scanner := bufio.NewScanner(os.Stdin)

	// gets username of bidder
	fmt.Print("Please enter your username: ")
	scanner.Scan()
	userName := scanner.Text()

	quit := "no"
	for quit != "yes" {
		fmt.Printf("Bid or Lookup (a/b/l)? ")
		fmt.Scanf("%s ", &cmd)
		// Calls function to add item
		if "a" == cmd {
			add(scanner)
		} else if "l" == cmd {
			// Calls function to lookup
			lookup(scanner)
		} else if "b" == cmd {
			// Calls function to bid
			bid(scanner, userName)
		} else if "q" == cmd {

		}

		// Gives user option to quit
		fmt.Print("Do you want to quit? (yes/no): ")
		fmt.Scanf("%s ", &quit)
	}

}
