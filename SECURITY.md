# Security Policy

## Supported Versions

This project is in active development. Security updates are provided for the latest version only.

| Version | Supported          |
| ------- | ------------------ |
| Latest  | :white_check_mark: |
| Older   | :x:                |

## Reporting a Vulnerability

**Please do not report security vulnerabilities through public GitHub issues.**

If you discover a security vulnerability in YimMenuV2, please report it responsibly:

1. **Email**: Contact the maintainers directly (check repository for contact info)
2. **Private Disclosure**: Use GitHub's private vulnerability reporting feature if available
3. **Information to Include**:
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if you have one)

### What to Expect

- **Initial Response**: Within 48 hours
- **Status Updates**: Every 3-5 days
- **Resolution Timeline**: Varies based on severity and complexity

### Scope

This security policy applies to:
- Code vulnerabilities that could compromise user systems
- Memory safety issues
- Injection vulnerabilities
- Code execution vulnerabilities

Out of scope:
- Game-specific exploits (these are for educational purposes)
- Issues in dependencies (report to upstream projects)

## Security Best Practices for Users

### Account Safety

1. **Use FSL** (recommended): Redirects save data to local storage
2. **Separate Account**: Use a separate account for modding
3. **Offline Testing**: Test features offline when possible
4. **Regular Backups**: Backup your game saves regularly

### Installation Safety

1. **Download from Official Sources**: Only download from official GitHub releases
2. **Verify Checksums**: Check SHA256 hashes when provided
3. **Scan Downloads**: Run antivirus scans on downloaded files
4. **Use Trusted Injectors**: Only use well-known, verified injectors

### General Safety

1. **Keep Updated**: Use the latest version of the mod
2. **Disable BattlEye**: As instructed in documentation
3. **Monitor Logs**: Check logs for unusual activity
4. **Report Issues**: Report suspicious behavior immediately

## Known Security Considerations

### Memory Manipulation

This project manipulates game memory and injects into the game process. This is inherently risky:

- **Anticheat Detection**: Online use may result in bans
- **Game Crashes**: Improper use may crash the game
- **Data Loss**: Always backup save data

### Code Injection

DLL injection is detected by:

- Anticheat systems (BattlEye must be disabled)
- Some antivirus software (may require whitelisting)
- System integrity checks

### Network Communication

When playing online:

- **Heartbeat Failures**: May be kicked from sessions
- **Data Transmission**: Modified data may be detected
- **Account Risk**: Online use risks account suspension

## Developer Security Guidelines

### Code Review

- All code must be reviewed before merging
- No AI-generated code (security and quality concerns)
- Focus on memory safety and validation

### Memory Safety

- Validate all pointers before dereferencing
- Use RAII for resource management
- Avoid buffer overflows
- Check array bounds

### Dependencies

- Keep dependencies updated
- Review dependency security advisories
- Audit third-party code before integration

### Secrets Management

- Never commit credentials or API keys
- Use environment variables for sensitive data
- Don't hardcode paths or identifiers

## Responsible Disclosure

We believe in responsible disclosure and will:

1. Acknowledge receipt of vulnerability reports
2. Work with reporters to understand the issue
3. Develop and test fixes privately
4. Coordinate public disclosure timing
5. Credit researchers (if desired)

## Additional Information

This is a modding tool for educational and entertainment purposes. Users assume all risks associated with:

- Account suspension or bans
- Game instability
- Data loss
- System security implications

Always use this software responsibly and at your own risk.

---

**Last Updated**: 2026-02-02
