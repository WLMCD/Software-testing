import unittest

class TestDataFlowTesting(unittest.TestCase):
    def setUp(self):
        self.sf = SoulmateFinder()

    def test_register_and_find_soulmate(self):
        # Test data for registration
        name = "Emily"
        age = 25
        gender = "F"
        interests = ["Reading", "Travel"]
        preferred_gender = "M"

        # Register a user
        sf = self.sf
        sf.register(name, age, gender, interests, preferred_gender)

        # Find soulmate for the registered user
        user = User(name, age, gender, interests, preferred_gender)
        age_range = 5
        same_interests = 1
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        self.assertGreater(len(results), 0)
        self.assertIn(user, results)

    def test_find_soulmate_no_matches(self):
        # Test data for finding soulmate
        name = "John"
        age = 30
        gender = "M"
        interests = ["Sports", "Music"]
        preferred_gender = "F"

        user = User(name, age, gender, interests, preferred_gender)
        age_range = 2
        same_interests = 2

        # Find soulmate for the user
        sf = self.sf
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        self.assertEqual(len(results), 0)

    def test_find_soulmate_multiple_matches(self):
        # Test data for finding soulmate
        name = "Alice"
        age = 28
        gender = "F"
        interests = ["Travel", "Sports"]
        preferred_gender = "M"

        user = User(name, age, gender, interests, preferred_gender)
        age_range = 3
        same_interests = 1

        # Find soulmate for the user
        sf = self.sf
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        self.assertGreater(len(results), 1)
        self.assertIn(user, results)

if __name__ == '__main__':
    unittest.main()
