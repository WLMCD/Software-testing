import unittest

class TestSoulmateFinder(unittest.TestCase):
    def setUp(self):
        self.sf = SoulmateFinder()

    def test_user_class_constructor(self):
        name = "John"
        age = 30
        gender = "M"
        interests = ["Sports", "Music"]
        preferred_gender = "F"
        user = User(name, age, gender, interests, preferred_gender)
        
        self.assertEqual(user.name, name)
        self.assertEqual(user.age, age)
        self.assertEqual(user.gender, gender)
        self.assertEqual(user.interests, interests)
        self.assertEqual(user.preferred_gender, preferred_gender)

    def test_soulmate_finder_register(self):
        name = "Emily"
        age = 25
        gender = "F"
        interests = ["Reading", "Travel"]
        preferred_gender = "M"

        sf = self.sf
        sf.register(name, age, gender, interests, preferred_gender)

        # Check if the user is added to the users list
        self.assertEqual(len(users), 1)
        self.assertEqual(users[0].name, name)
        self.assertEqual(users[0].age, age)
        self.assertEqual(users[0].gender, gender)
        self.assertEqual(users[0].interests, interests)
        self.assertEqual(users[0].preferred_gender, preferred_gender)

    def test_soulmate_finder_find_soulmate(self):
        user = User("John", 30, "M", ["Sports", "Music"], "F")
        age_range = 5
        same_interests = 1

        sf = self.sf
        results = sf.find_soulmate(user, age_range, same_interests)

        # Perform assertions on the results
        self.assertIsInstance(results, list)
        # Additional assertions on the results can be added based on specific requirements

if __name__ == '__main__':
    unittest.main()
