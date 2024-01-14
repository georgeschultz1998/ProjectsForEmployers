package com.example.flashcardapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    private Spinner arraySpinner;
    private Button newFlashCardButton;
    private Button viewFlashCardsButton;
    private Button addArrayButton;
    private String[] demoQuestionArray = {
            "What is React Native?",
            "What are some benefits of using React Native?",
            "What are some limitations of React Native?",
            "What is JSX?",
            "What is the difference between React and React Native?"
    };

    private String[] demoAnswerArray = {
            "React Native is a JavaScript framework used for building mobile applications.",
            "React Native allows for cross-platform development, code reusability, and hot reloading for faster development.",
            "React Native has limitations with performance, access to native APIs, and certain platform-specific features.",
            "JSX is a syntax extension for JavaScript that allows for writing HTML-like code in JavaScript files.",
            "React is a JavaScript library used for building user interfaces in web applications, while React Native is used for building mobile applications."
    };

    private String[] questionArray = {};
    private String[] answerArray = {};
    private String[][][] flashCardArrays = {
            {demoQuestionArray, demoAnswerArray},
            {questionArray, answerArray},
    };



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize the UI components
        arraySpinner = findViewById(R.id.arraySpinner);
        newFlashCardButton = findViewById(R.id.newFlashCardButton);
        viewFlashCardsButton = findViewById(R.id.viewFlashCardsButton);
        addArrayButton = findViewById(R.id.addArrayButton);

        // Set up the spinner with the array names
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(this,
                android.R.layout.simple_spinner_dropdown_item, getArrayNames());
        arraySpinner.setAdapter(arrayAdapter);

        // Set onClick listeners for the buttons
        newFlashCardButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, NewFlashCardActivity.class);
                int selectedArrayIndex = arraySpinner.getSelectedItemPosition();
                intent.putExtra("questionArray", flashCardArrays[selectedArrayIndex][0]);
                intent.putExtra("answerArray", flashCardArrays[selectedArrayIndex][1]);
                intent.putExtra("selectedArrayIndex", selectedArrayIndex);
                startActivityForResult(intent, 1);
            }
        });

        viewFlashCardsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int selectedArrayIndex = arraySpinner.getSelectedItemPosition();
                if (flashCardArrays[selectedArrayIndex][0].length == 0) {
                    Toast.makeText(MainActivity.this, "Flashcard set is empty, you must add a card first to view.", Toast.LENGTH_SHORT).show();
                } else {
                    Intent intent = new Intent(MainActivity.this, ViewFlashCardsActivity.class);
                    intent.putExtra("questionArray", flashCardArrays[selectedArrayIndex][0]);
                    intent.putExtra("answerArray", flashCardArrays[selectedArrayIndex][1]);
                    intent.putExtra("selectedArrayIndex", selectedArrayIndex);
                    startActivityForResult(intent, 1);
                }
            }
        });



        addArrayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Add a new empty array to the list of arrays
                String[][][] newFlashCardArrays = Arrays.copyOf(flashCardArrays, flashCardArrays.length + 1);
                newFlashCardArrays[newFlashCardArrays.length - 1] = new String[][]{questionArray, answerArray};
                flashCardArrays = newFlashCardArrays;

                // Update the spinner with the new array name
                ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(MainActivity.this,
                        android.R.layout.simple_spinner_dropdown_item, getArrayNames());
                arraySpinner.setAdapter(arrayAdapter);
            }
        });

    }

    private String[] getArrayNames() {
        String[] arrayNames = new String[flashCardArrays.length];
        arrayNames[0] = "Demo FlashCard Set ";
        for (int i = 1; i < flashCardArrays.length; i++) {
            arrayNames[i] = "Custom FlashCard Set " + (i);
        }
        return arrayNames;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == 1) {
            if (resultCode == RESULT_OK) {
                ArrayList<String> updatedQuestionList = data.getStringArrayListExtra("updatedQuestionList");
                ArrayList<String> updatedAnswerList = data.getStringArrayListExtra("updatedAnswerList");
                int selectedArrayIndex = data.getIntExtra("selectedArrayIndex", -1);
                if (selectedArrayIndex != -1 && updatedQuestionList != null && updatedAnswerList != null) {
                    Log.d("MainActivity", "Updated question list size: " + updatedQuestionList.size());
                    Log.d("MainActivity", "Updated answer list size: " + updatedAnswerList.size());
                    flashCardArrays[selectedArrayIndex][0] = updatedQuestionList.toArray(new String[updatedQuestionList.size()]);
                    flashCardArrays[selectedArrayIndex][1] = updatedAnswerList.toArray(new String[updatedAnswerList.size()]);
                } else {
                    Log.e("MainActivity", "Updated question or answer list is null or selectedArrayIndex is invalid");
                }
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }


}
