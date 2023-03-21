
'''
Copy this file and run `pbpaste | base64` to generate challenge text. Copious
white space is at the bottom of the file to ensure trailing `==` and hint at
base64.
'''

import codecs
import string
import sys
import time

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.hashes import SHA1
from cryptography.hazmat.primitives.twofactor.totp import TOTP

ONE_WEEK_IN_SECONDS = 604_800


def generate_secret():
    totp = TOTP(
        key=codecs.encode(string.ascii_letters, encoding="utf-8"),
        length=8,
        algorithm=SHA1(),
        time_step=ONE_WEEK_IN_SECONDS,
        backend=default_backend(),
    )
    seed = 0
    token = codecs.decode(totp.generate(seed), encoding="utf-8")
    return f"{token}-{seed}"


if __name__ == "__main__":
    sys.stdout.write(
        f"Please head to https://ramp.com/careers and use this secret when "
        f"you apply: {generate_secret()}\n"
    )


