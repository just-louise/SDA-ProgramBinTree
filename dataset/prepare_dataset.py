import json
import re
from pathlib import Path
from typing import Dict, List, Any, Tuple

# ==================================================
# CONFIGURATION
# ==================================================
INPUT_FILE = "dict.json"
OUTPUT_FILE = "kamus.txt"

TARGET_ENTRY_COUNT = 5000
MAX_SYNONYMS = 5
MIN_SYNONYMS = 2
MIN_WORD_LENGTH = 3
MAX_WORD_LENGTH = 18

STOPWORDS = {
    "-", "--", "dll", "dsb", "dst"
}
LABELS_TO_REMOVE = ["ki", "cak", "ark", "mk", "pb", "kp"]

# ==================================================
# REGEX PATTERNS
# ==================================================
PARENTHESES_PATTERN = re.compile(r"\(.*?\)")
MULTIPLE_SPACES_PATTERN = re.compile(r"\s+")
LABEL_PATTERN = re.compile(rf"^(?:{'|'.join(LABELS_TO_REMOVE)})\s+", re.IGNORECASE)

CONTAINS_DIGIT_PATTERN = re.compile(r"\d")
CONTAINS_HTML_PATTERN = re.compile(r"&[a-zA-Z0-9#]+;|<[^>]+>")

# ==================================================
# STATISTICS TRACKER
# ==================================================
class Stats:
    def __init__(self):
        self.original_entries = 0
        self.invalid_words_removed = 0
        self.invalid_synonyms_removed = 0
        self.duplicate_synonyms_removed = 0
        self.final_entries = 0
        self.output_entries = 0

# ==================================================
# HELPER FUNCTIONS
# ==================================================
def is_valid_word(word: str) -> bool:
    """Validate word based on length, printable characters, word count, and invalid contents."""
    if len(word) < MIN_WORD_LENGTH or len(word) > MAX_WORD_LENGTH:
        return False
        
    if not word.isprintable():
        return False
        
    # maximum 2 words
    if len(word.split()) > 2:
        return False
        
    # no digits
    if CONTAINS_DIGIT_PATTERN.search(word):
        return False
        
    # no HTML entities
    if CONTAINS_HTML_PATTERN.search(word):
        return False
        
    # no tabs/newlines
    if re.search(r'[\t\n\r]', word):
        return False
        
    return True

def clean_synonym(synonym: str) -> str:
    """Apply cleaning rules like removing labels, parentheses, and spaces."""
    # remove text inside ()
    cleaned = PARENTHESES_PATTERN.sub("", synonym)
    # trim spaces
    cleaned = cleaned.strip()
    # remove thesaurus labels
    cleaned = LABEL_PATTERN.sub("", cleaned)
    # collapse multiple spaces
    cleaned = MULTIPLE_SPACES_PATTERN.sub(" ", cleaned)
    # final trim just to be sure
    return cleaned.strip()

def is_valid_synonym(synonym: str) -> bool:
    """Check against stopwords, empty strings, HTML, and digits."""
    if not synonym:
        return False
        
    syn_lower = synonym.lower()
    
    if syn_lower in STOPWORDS:
        return False
        
    if CONTAINS_DIGIT_PATTERN.search(synonym):
        return False
        
    if CONTAINS_HTML_PATTERN.search(synonym):
        return False
        
    return True

# ==================================================
# MAIN PROCESSING
# ==================================================
def prepare_dataset(input_path: Path, output_path: Path) -> None:
    stats = Stats()
    
    if not input_path.exists():
        print(f"Error: Input file {input_path} not found.")
        return

    print("Loading JSON dataset...")
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            data: Dict[str, Any] = json.load(f)
    except json.JSONDecodeError:
        print(f"Error: File {input_path} is not valid JSON.")
        return

    stats.original_entries = len(data)
    processed_entries: List[Tuple[str, List[str]]] = []
    
    print("Processing entries...")
    for main_word, word_data in data.items():
        main_word = main_word.strip()
        main_word_lower = main_word.lower()
        
        # Word Filter
        if not is_valid_word(main_word):
            stats.invalid_words_removed += 1
            continue
            
        raw_synonyms = word_data.get("sinonim", [])
        if not raw_synonyms or not isinstance(raw_synonyms, list):
            continue
            
        # Synonym Cleaning
        seen = set()
        cleaned_synonyms = []
        
        for syn in raw_synonyms:
            cleaned = clean_synonym(syn)
            cleaned_lower = cleaned.lower()
            
            # remove synonym equal to main word
            if cleaned_lower == main_word_lower:
                stats.invalid_synonyms_removed += 1
                continue
                
            # Validations: stopwords, empty, HTML, digits
            if not is_valid_synonym(cleaned):
                stats.invalid_synonyms_removed += 1
                continue
                
            # remove duplicates
            if cleaned_lower in seen:
                stats.duplicate_synonyms_removed += 1
                continue
                
            seen.add(cleaned_lower)
            cleaned_synonyms.append(cleaned)
            
        # Keep only the first 5 cleaned synonyms
        cleaned_synonyms = cleaned_synonyms[:MAX_SYNONYMS]
        
        # If fewer than 2 valid synonyms remain, discard the word
        if len(cleaned_synonyms) < MIN_SYNONYMS:
            continue
            
        processed_entries.append((main_word, cleaned_synonyms))
        
    stats.final_entries = len(processed_entries)
    
    # Output Sorting & Sizing
    # Sort alphabetically
    processed_entries.sort(key=lambda x: x[0].lower())
    
    # Keep the first 5000 entries
    output_entries = processed_entries[:TARGET_ENTRY_COUNT]
    stats.output_entries = len(output_entries)
    
    # Output to File
    print("Writing to output file...")
    with open(output_path, 'w', encoding='utf-8') as f:
        for main_word, synonyms in output_entries:
            f.write(f"{main_word},{','.join(synonyms)}\n")
            
    # Print Statistics
    print("\n==================================================")
    print("STATISTICS")
    print("==================================================")
    print(f"Original JSON entries:      {stats.original_entries}")
    print(f"Invalid words removed:      {stats.invalid_words_removed}")
    print(f"Invalid synonyms removed:   {stats.invalid_synonyms_removed}")
    print(f"Duplicate synonyms removed: {stats.duplicate_synonyms_removed}")
    print(f"Final valid entries:        {stats.final_entries}")
    print(f"Written entries:            {stats.output_entries}")
    print("==================================================\n")

def main() -> None:
    base_dir = Path(__file__).parent
    input_path = base_dir / INPUT_FILE
    output_path = base_dir / OUTPUT_FILE
    
    prepare_dataset(input_path, output_path)

if __name__ == "__main__":
    main()
