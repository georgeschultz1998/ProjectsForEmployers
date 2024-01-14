package com.example.flashcardapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.content.Intent;

import java.util.ArrayList;
import java.util.Arrays;

public class NewFlashCardActivity extends AppCompatActivity {

    private EditText questionEditText;
    private EditText answerEditText;
    private Button saveFlashCardButton;

    private String[] questionArray;
    private String[] answerArray;
    private int selectedArrayIndex;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_flash_card);

        questionEditText = findViewById(R.id.questionEditText);
        answerEditText = findViewById(R.id.answerEditText);
        saveFlashCardButton = findViewById(R.id.saveFlashCardButton);

        // Retrieve the question and answer arrays that were passed from MainActivity
        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            questionArray = extras.getStringArray("questionArray");
            answerArray = extras.getStringArray("answerArray");
            selectedArrayIndex = extras.getInt("selectedArrayIndex");
        }

        saveFlashCardButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveFlashCard();
            }
        });
    }


    private void saveFlashCard() {
        String question = questionEditText.getText().toString().trim();
        String answer = answerEditText.getText().toString().trim();

        if (question.isEmpty() || answer.isEmpty()) {
            Toast.makeText(this, R.string.flash_card_empty_error, Toast.LENGTH_SHORT).show();
            return;
        }

        // Add the new question and answer to the arrays
        ArrayList<String> newQuestionList = new ArrayList<>(Arrays.asList(questionArray));
        ArrayList<String> newAnswerList = new ArrayList<>(Arrays.asList(answerArray));
        newQuestionList.add(question);
        newAnswerList.add(answer);

        Toast.makeText(this, R.string.flash_card_saved, Toast.LENGTH_SHORT).show();

        // Pass the updated arrays back to MainActivity
        Intent intent = new Intent();
        intent.putStringArrayListExtra("updatedQuestionList", newQuestionList);
        intent.putStringArrayListExtra("updatedAnswerList", newAnswerList);
        intent.putExtra("selectedArrayIndex", selectedArrayIndex);
        setResult(RESULT_OK, intent);
        finish();
    }


}
