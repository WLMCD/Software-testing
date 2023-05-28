import unittest
from unittest.mock import patch

class TestSoulmateFinderIntegration(unittest.TestCase):
    def test_register_and_find_soulmate(self):
        sf = SoulmateFinder()

        # Register a user
        name = "Emily"
        age = 25
        gender = "F"
        interests = ["Reading", "Travel"]
        preferred_gender = "M"
        sf.register(name, age, gender, interests, preferred_gender)

        # Find soulmate for the registered user
        user = User(name, age, gender, interests, preferred_gender)
        age_range = 5
        same_interests = 1
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        # Additional assertions on the results can be added based on specific requirements

    def test_find_soulmate_without_registering(self):
        sf = SoulmateFinder()

        # Find soulmate without registering a user
        name = "John"
        user = User(name, 30, "M", ["Sports", "Music"], "F")
        age_range = 5
        same_interests = 1
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        # Additional assertions on the results can be added based on specific requirements

if __name__ == '__main__':
    unittest.main()
