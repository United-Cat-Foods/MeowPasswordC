Feature: Help and Information
  As a user of MeowPassword
  I want to view help information
  So that I understand how to use the tool

  Scenario: Display help with --help flag
    When I run meowpass with "--help"
    Then the exit code should be 0
    And the output should contain "Usage: meowpass [options]"
    And the output should contain "--numbers"
    And the output should contain "--symbols"
    And the output should contain "--max-length"
    And the output should contain "--test"
    And the output should contain "--copy"

  Scenario: Display help with -h flag
    When I run meowpass with "-h"
    Then the exit code should be 0
    And the output should contain "Usage: meowpass [options]"
