package com.example.flashcardapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class ViewFlashCardsActivity extends AppCompatActivity {

    private TextView questionAnswerTextView;
    private Button prevButton;
    private Button nextButton;
    private TextView cardNumberTextView;

    private int currentCardIndex = 0;

    private String[] questionArray;
    private String[] answerArray;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_flash_cards);

        questionAnswerTextView = findViewById(R.id.questionAnswerTextView);
        prevButton = findViewById(R.id.prevButton);
        nextButton = findViewById(R.id.nextButton);
        cardNumberTextView = findViewById(R.id.cardNumberTextView);

        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            questionArray = extras.getStringArray("questionArray");
            answerArray = extras.getStringArray("answerArray");
        }

        showQuestion();

        questionAnswerTextView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (questionAnswerTextView.getText().toString().equals(questionArray[currentCardIndex])) {
                    showAnswer();
                } else {
                    showQuestion();
                }
            }
        });

        prevButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (currentCardIndex == 0) {
                    currentCardIndex = questionArray.length - 1;
                } else {
                    currentCardIndex--;
                }
                showQuestion();
            }
        });

        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (currentCardIndex == questionArray.length - 1) {
                    currentCardIndex = 0;
                } else {
                    currentCardIndex++;
                }
                showQuestion();
            }
        });
    }

    private void showQuestion() {
        questionAnswerTextView.setText(questionArray[currentCardIndex]);
        cardNumberTextView.setText("Card " + (currentCardIndex + 1) + " of " + questionArray.length);
    }

    private void showAnswer() {
        questionAnswerTextView.setText(answerArray[currentCardIndex]);
        cardNumberTextView.setText("Card " + (currentCardIndex + 1) + " of " + questionArray.length);
    }
}
