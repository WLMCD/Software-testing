import unittest
from unittest.mock import patch
from io import StringIO

class TestSoulmateFinderUserAcceptance(unittest.TestCase):
    def setUp(self):
        self.sf = SoulmateFinder()

    def test_register_successful(self):
        name = "Emily"
        age = 25
        gender = "F"
        interests = ["Reading", "Travel"]
        preferred_gender = "M"

        sf = self.sf

        # Redirect stdout to capture the print statements
        with patch('sys.stdout', new=StringIO()) as fake_out:
            sf.register(name, age, gender, interests, preferred_gender)

            # Check if the registration success message is printed
            self.assertIn(f"User {name} registered successful!", fake_out.getvalue().strip())

            # Check if the user is added to the users list
            self.assertEqual(len(users), 1)
            self.assertEqual(users[0].name, name)
            self.assertEqual(users[0].age, age)
            self.assertEqual(users[0].gender, gender)
            self.assertEqual(users[0].interests, interests)
            self.assertEqual(users[0].preferred_gender, preferred_gender)

    def test_find_soulmate_no_matches(self):
        user = User("John", 30, "M", ["Sports", "Music"], "F")
        age_range = 5
        same_interests = 2

        sf = self.sf

        # Redirect stdout to capture the print statements
        with patch('sys.stdout', new=StringIO()) as fake_out:
            sf.find_soulmate(user, age_range, same_interests)

            # Check if the no matches message is printed
            self.assertIn("No potential matches found at the moment.", fake_out.getvalue().strip())

    def test_find_soulmate_with_matches(self):
        user = User("Emily", 25, "F", ["Reading", "Travel"], "M")
        age_range = 5
        same_interests = 1

        sf = self.sf

        # Redirect stdout to capture the print statements
        with patch('sys.stdout', new=StringIO()) as fake_out:
            sf.find_soulmate(user, age_range, same_interests)

            # Check if the matches are printed
            self.assertIn("Here are some potential matches for you:", fake_out.getvalue().strip())

    def test_find_soulmate_best_match(self):
        user = User("Emily", 25, "F", ["Reading", "Travel"], "M")
        age_range = 5
        same_interests = 2

        sf = self.sf

        # Redirect stdout to capture the print statements
        with patch('sys.stdout', new=StringIO()) as fake_out:
            sf.find_soulmate(user, age_range, same_interests)

            # Check if the best match is printed
            self.assertIn("And your best match is:", fake_out.getvalue().strip())

if __name__ == '__main__':
    unittest.main()
