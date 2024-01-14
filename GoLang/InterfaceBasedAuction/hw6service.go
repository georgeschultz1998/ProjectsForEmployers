// Copyright 2010 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// An edited version of code from the Go tutorials
// that supports a service that manages email contacts

package main

import (
	"fmt"
	"log"
	"net/http"
	"regexp"
	"strconv"
)

// Describes valid subpaths that allow for add lookup or bid
var validPath = regexp.MustCompile(`^/(add|lookup|bid)$`)

// Port for clients to connect to
var PORT_STR = ":8080"

// Takes a function that handles HTTP requests
// Wraps call to this function with code to ensure
// URL is valid
func makeHandler(fn func(http.ResponseWriter, *http.Request)) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {

		m := validPath.FindStringSubmatch(r.URL.Path)
		if m == nil {
			http.NotFound(w, r)
			return
		}
		fn(w, r)
	}
}

// Where items, item current bids, item min bid, & the bid persons are stored
var itemTable map[string]string
var bidTable map[string]int
var bidMinTable map[string]int
var bidPersonTable map[string]string

// Supports requests to add an item, item details, & min bid of item.
func addHandler(w http.ResponseWriter, r *http.Request) {
	name := r.URL.Query().Get("name")
	desc := r.URL.Query().Get("desc")
	minBid := r.URL.Query().Get("minBid")
	itemTable[name] = desc
	bidMinTable[name], _ = strconv.Atoi(minBid)
	//fmt.Fprint(w, "Added ", name, " Desc: ", desc)
	return
}

// Supports looking up an item based on its name
func lookupHandler(w http.ResponseWriter, r *http.Request) {
	name := r.URL.Query().Get("name")
	desc, exists := itemTable[name]
	if !exists {
		fmt.Fprint(w, name, " not found\n")
		return
	}

	minBid := bidMinTable[name]

	bidder, exists := bidPersonTable[name]
	var curBid int = 0
	if !exists {
		//fmt.Fprintln(w, name, " has no bidders")
		bidder = "0 "
	} else {
		curBid = bidTable[name]
	}

	if minBid > curBid {
		curBid = minBid
	}

	if bidder == "0 " {
		fmt.Fprint(w, "The item details are: {", name, " ", desc, " ", minBid, " {", bidder, "}}\n")
	} else {
		fmt.Fprint(w, "The item details are: {", name, " ", desc, " ", minBid, " {", curBid, " ", bidder, "}}\n")
	}
}

// function allows a user to bid on an item
func bidHandler(w http.ResponseWriter, r *http.Request) {
	// gets the item being bid on name for table searching, the amount being bid on,  & the user bidding.
	name := r.URL.Query().Get("name")
	strAmount := r.URL.Query().Get("amount")
	userName := r.URL.Query().Get("userName")

	bidAmount, err := strconv.Atoi(strAmount)

	if err != nil {
		fmt.Fprint(w, err)
	}

	// Retrieves the current bid & minbid from their respective tables.
	curBid := bidTable[name]
	minBid := bidMinTable[name]

	if bidAmount < minBid {
		// Handles when bid amount is less than min bid
		fmt.Fprint(w, "$", bidAmount, " is below the minimum bid of $US ", minBid, "\n")
	} else if bidAmount <= curBid {
		// Handles when bid amount is less than or equal to current bid
		fmt.Fprint(w, "$", bidAmount, " is not greater than the current high bid of", curBid, "\n")
	} else {
		//fmt.Fprint(w, "Bid Accepted")
		// Handles when bid is high enough. Saves bidder name and bid to tables
		bidPersonTable[name] = userName
		bidTable[name] = bidAmount
	}
}

func main() {
	//define the tables being used
	bidPersonTable = make(map[string]string)
	itemTable = make(map[string]string)
	bidTable = make(map[string]int)
	bidMinTable = make(map[string]int)

	http.HandleFunc("/lookup", makeHandler(lookupHandler))
	http.HandleFunc("/add", makeHandler(addHandler))
	http.HandleFunc("/bid", makeHandler(bidHandler))

	log.Fatal(http.ListenAndServe(PORT_STR, nil))
}
