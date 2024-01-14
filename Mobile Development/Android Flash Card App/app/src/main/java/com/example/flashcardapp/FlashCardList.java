package com.example.flashcardapp;
import java.util.ArrayList;
import java.util.List;

public class FlashCardList {

    private static ArrayList<FlashCard> flashCards = new ArrayList<>();

    public static ArrayList<FlashCard> getFlashCards() {
        return flashCards;
    }

    public static void addFlashCard(FlashCard flashCard) {
        flashCards.add(flashCard);
    }

    public static void removeFlashCard(FlashCard flashCard) {
        flashCards.remove(flashCard);
    }
}
