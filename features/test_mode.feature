Feature: Built-in Test Mode
  As a developer of MeowPassword
  I want to run the built-in test suite
  So that I can verify core functionality

  Scenario: Run built-in tests
    When I run meowpass with "--test"
    Then the exit code should be 0
    And the output should contain "Running Basic MeowPassword Tests"
    And the output should contain "Passed:"
    And the output should not contain "FAIL:"
