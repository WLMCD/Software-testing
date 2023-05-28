import unittest
from unittest.mock import patch
from mutmut import mutate

class TestSoulmateFinder(unittest.TestCase):
    def setUp(self):
        self.sf = SoulmateFinder()

    def test_soulmate_finder_find_soulmate(self):
        # Generate mutant by modifying the condition in find_soulmate method
        with patch('random.choice', return_value=False):  # Mock the random.choice function to always return False
            mutant_code = mutate(SoulmateFinder.find_soulmate)
        
        # Create a new class with the mutant code
        class MutantSoulmateFinder(SoulmateFinder):
            find_soulmate = mutant_code
        
        user = User("John", 30, "M", ["Sports", "Music"], "F")
        age_range = 5
        same_interests = 1

        sf = MutantSoulmateFinder()  # Use the mutant class for testing
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        # Additional assertions on the results can be added based on specific requirements

if __name__ == '__main__':
    unittest.main()
