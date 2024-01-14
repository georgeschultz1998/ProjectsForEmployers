package main

// imports
import "fmt"
import "log"
import "math/rand"
import "time"
import "strconv"

type IPlayer interface{
	guess() int
}

// methods
// this generates a random integer with a max and min value
func randInt(min,max int) int{
	return min + rand.Intn(max-min)
}

// Structures
// this is the struct for Game
type Game struct {
	player IPlayer
	nGuesses int  //number of guesses made so far
	nMatches int  //randomly generated number the user is trying to match
	recentGuess int //most recent guess of number
}

// This plays the game by calling the players guess()  to get the next guess
// and outputing the appropriate response
func (g *Game) play() {
	var guesser="None"
  var minV int =1
  var maxV int =10
	rand.Seed(time.Now().UnixNano())
	g.nMatches=randInt(minV,maxV) // defines the random guess
	var ans string
	fmt.Println("You have 3 guesses to guess an number from 1 to 10")
	fmt.Println("Do you want to make the guesses? (y/n -- if n guesses will be generated for you): ")
	n,err := fmt.Scanln(&ans)
	if err != nil { log.Fatal(err) }
  n+=1  //not used

	// choose the player for the game based on input ans
	if(ans=="y"){
	// Human player
		g.player=Human{}
    guesser = ""

	} else {
	// computer player define the player
		g.player=AutoGuess{minV,maxV,g}
    guesser = ""
	}

	// now loop through the number of guess's
	
	var guessesMade=1
	var intAns int
	var value int
	value=g.nMatches

	for guessesMade <= g.nGuesses {
		intAns=g.player.guess()
    g.recentGuess=intAns
		if(intAns>value) {
			fmt.Printf("%sToo high\n",guesser)
      maxV=intAns  //adjust maxV
		} else if(intAns<value){
			fmt.Printf("%sToo low \n",guesser)
      minV=intAns  //adjust minV
		} else{
			break
		}
    if (ans=="n"){
    g.player=AutoGuess{minV,maxV,g} //after adjusting min and max value init g.player
      }
		guessesMade++	
	}// end of for loop

	if(guessesMade>g.nGuesses){
		fmt.Println("You ran out of guesses. Game over")
	} else {
		fmt.Println("You win!")	
	}
} // end of game


// human structure
type Human struct {

}

// asks the human user for the next number to guess
func (h Human) guess() (num int) {
	var guess string
	fmt.Println("Enter your next guess: ")

	n,err := fmt.Scanln(&guess)
	if err != nil { log.Fatal(err) }
  n+=1

	intAns,err:=strconv.Atoi(guess)
	if err !=nil{log.Fatal(err)}
	return intAns

} // end of guess for human


// Computer Struct and Function
type AutoGuess struct {
	minValues int
	maxValues int
	theGame *Game
}

// will retun an appropriate guess based on random gen. number
func (a AutoGuess) guess() (num int) {
  var v int
  v=(a.maxValues+a.minValues)/2
    fmt.Println("The computer has chosen ", v)
  
	return v

}// end of guess for computer


// main
func main() {
	// init game
	fmt.Println("Guess a number to demo interfaces")
	g:=Game{}
	g.nGuesses=3
	g.nMatches=randInt(1,10)
	g.play()
}