package phonics.com.phonicsapp;

import com.google.firebase.database.IgnoreExtraProperties;

/**
 * Card class holds all the data for a word.
 * Contains getters and setters for the word, definition,
 * and synonym.
 */
@IgnoreExtraProperties
public class Card {
    private String word;
    private String def;
    private String synonym;

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public String getDef() {
        return def;
    }

    public void setDef(String def) {
        this.def = def;
    }

    public String getSynonym() {
        return synonym;
    }

    public void setSynonym(String synonym) {
        this.synonym = synonym;
    }

    public Card(String word, String definition, String synonym) {
        this.word = word;
        this.def = definition;
        this.synonym = synonym;
    }
}
